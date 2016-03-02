///////////////////////////////////////////////////////////////////
/*
 * Mentor System Application
 * System for Telemementoring with Augmented Reality (STAR) Project
 * Intelligent Systems and Assistive Technology (ISAT) Laboratory
 * Purdue University School of Industrial Engineering
 * 
 * Code programmed by: Edgar Javier Rojas Muñoz
 * advised by the professor: Juan Pablo Wachs, Ph.D
 */
//---------------------------------------------------------------//
/*                        CODE OVERVIEW
 * Name: JSONManager.cpp
 *
 * Overview: .cpp of JSONManager.h
 */
///////////////////////////////////////////////////////////////////

//Include its header file
#include "JSONManager.h"

/*
 * Method Overview: Constructor of the class
 * Parameters: Instance of the Communication Manager server
 * Return: Instance of the class
 */
JSONManager::JSONManager(CommunicationManager* pManager, CommandCenter* pCommander)
{
	myCommunicationManager = pManager;

	myCommander = pCommander;
}

/*
 * Method Overview: Infinite loop to start the JSON creation
 * Parameters: None
 * Return: None
 */
void JSONManager::constructGeneralJSON()
{
	while(1)
	{
		if((int)(JSONs_to_create.size())>0)
		{
			if(!(myCommander->getJSONCreationFlag()))
			{
				myCommander->setJSONCreationFlag(1);

				JSONable to_create = JSONs_to_create.front();

				const char* command_char = (to_create.command).c_str();

				if(strcmp(CREATE_ANNOTATION_COMMAND, command_char) == 0)
				{
					if(to_create.annotation_code==NULL)
					{
						constructLineJSONMessage(to_create.id, to_create.command, to_create.myPoints);
					}
					else
					{
						constructVirtualAnnotationJSONMessage(to_create.id, to_create.command, to_create.annotation_code, to_create.annotation_information);
					}
				}
				else if(strcmp(UPDATE_ANNOTATION_COMMAND, command_char) == 0)
				{
					if(to_create.annotation_code==NULL)
					{
						constructLineJSONMessage(to_create.id, to_create.command, to_create.myPoints);
					}
					else
					{
						constructVirtualAnnotationJSONMessage(to_create.id, to_create.command, to_create.annotation_code, to_create.annotation_information);
					}
				}
				else if(strcmp(DELETE_ANNOTATION_COMMAND, command_char) == 0)
				{
					constructDeleteJSONMessage(to_create.command, to_create.selected_annotation_id);
				}
				JSONs_to_create.pop();
			}
		}
	}
}

/*
 * Method Overview: Constructs a JSON Value object of a line
 * Parameters: Required values of the object to create
 * Return: None
 */
void JSONManager::createJSONable(int id, string command, vector<long double>* myPoints, int annotation_code, 
		vector<double> annotation_information, vector<int> selected_annotation_id)
{
	JSONable to_add;

	to_add.id = id;
	to_add.command = command;
	to_add.myPoints = myPoints;
	to_add.annotation_code = annotation_code;


	to_add.annotation_information = annotation_information;
	to_add.selected_annotation_id = selected_annotation_id;

	JSONs_to_create.push(to_add);

}

/*
 * Method Overview: Constructs a JSON Value object of a line
 * Parameters (1): Line Id, message command, points of the line
 * Parameters (2): Vector of Ids of the lines to erase (if any)
 * Return: None
 */
void JSONManager::constructLineJSONMessage(int id, string command, vector<long double>* myPoints)
{
	/*
	 * Json::arrayValue = empty array []
	 * Json::objectValue = empty object {}
	 */

	Json::Value message;
	Json::Value annotation_memory;
	Json::Value initialAnnotation;
	Json::Value annotationPoints;
	
	message["id"] = id;
	message["command"] = command;

	annotation_memory["matches"] = Json::objectValue;
	annotation_memory["initialKeyPoints"] = Json::arrayValue;
	annotation_memory["initialDescriptors"] = Json::objectValue;

	int counter;

	for(counter = 0; counter<(int)myPoints->size();counter=counter+2)
	{
		annotationPoints["x"] = (double)(myPoints->at(counter)/RESOLUTION_X);
		annotationPoints["y"] = (double)((RESOLUTION_Y-(myPoints->at(counter+1)))/RESOLUTION_Y);

		initialAnnotation["annotationPoints"].append(annotationPoints);
	}

	initialAnnotation["annotationType"] = POLYLINE_ANNOTATION;

	annotation_memory["initialAnnotation"] = initialAnnotation;
	annotation_memory["currentAnnotation"] = initialAnnotation;
	annotation_memory["currentHomography"] = Json::objectValue;
	annotation_memory["initialRawKeyPoints"] = Json::arrayValue;
	annotation_memory["currentRawKeyPoints"] = Json::arrayValue;

	message["annotation_memory"] = annotation_memory;

	//Writes JSON Value to a file
	writeJSONonFile(message);
}

/*
 * Method Overview: Constructs a JSON Value object of an annotation
 * Parameters (1): Annotation Id, message command, annotation_code
 * Parameters (2): Annotation's important information
 * Parameters (3): Vector of Ids of the lines to erase (if any)
 * Return: None
 */
void JSONManager::constructVirtualAnnotationJSONMessage(int id, string command, int annotation_code, vector<double> annotation_information)
{
	/*
	 * The annotation_information structure contains:
	 * annotation_information[0] = annotation center X coordinate
	 * annotation_information[1] = annotation center Y coordinate
	 * annotation_information[2] = annotation rotation value
	 * annotation_information[3] = annotation zoom value
	 */	

	string annotation_name = findAnnotationName(annotation_code);

	Json::Value message;
	Json::Value annotation_memory;
	Json::Value annotationPoints;
	Json::Value initialAnnotation;
	
	message["id"] = id;
	message["command"] = command;

	annotation_memory["matches"] = Json::objectValue;
	annotation_memory["initialKeyPoints"] = Json::arrayValue;
	annotation_memory["initialDescriptors"] = Json::objectValue;

	annotationPoints["x"] = (annotation_information[0]/RESOLUTION_X);
	annotationPoints["y"] = (annotation_information[1]/RESOLUTION_Y);

	initialAnnotation["annotationPoints"].append(annotationPoints);
	initialAnnotation["rotation"] = -1*(annotation_information[2]);
	initialAnnotation["scale"] = annotation_information[3];
	initialAnnotation["annotationType"] = VIRTUAL_TOOL_ANNOTATION;
	initialAnnotation["toolType"] = annotation_name;
	initialAnnotation["selectableColor"] = 0;

	annotation_memory["initialAnnotation"] = initialAnnotation;
	annotation_memory["currentAnnotation"] = initialAnnotation;
	annotation_memory["currentHomography"] = Json::objectValue;
	annotation_memory["initialRawKeyPoints"] = Json::arrayValue;
	annotation_memory["currentRawKeyPoints"] = Json::arrayValue;

	message["annotation_memory"] = annotation_memory;

	//Writes JSON Value to a file
	writeJSONonFile(message);
}

/*
 * Method Overview: Creates a JSON Message of a delete command
 * Parameters: Command type, ID of the erased annotations
 * Return: None
 */
void JSONManager::constructDeleteJSONMessage(string command, vector<int> selected_annotation_id)
{
	Json::Value message;

	message["command"] = command;

	int counter;
	for(counter = 0; counter<(int)selected_annotation_id.size();counter++)
	{
		message["id"].append(selected_annotation_id.at(counter));
	}

	//Writes JSON Value to a file
	writeJSONonFile(message);
}

/*
 * Method Overview: Retrieves the annotation name
 * Parameters: Annotation code
 * Return: Annotation name
 */
string JSONManager::findAnnotationName(int code)
{
	string annotation_name = "";

	switch(code)
	{
		case BVM_CODE:
			annotation_name = BVM;
			break;

		case ETTUBE_CODE:
			annotation_name = ETTUBE;
			break;

		case HEMOSTAT_CODE:
			annotation_name = HEMOSTAT;
			break;

		case IODINE_SWAB_CODE:
			annotation_name = IODINESWAB;
			break;

		case LONGHOOK_CODE:
			annotation_name = LONGHOOK;
			break;

		case RETRACTOR_CODE:
			annotation_name = RETRACTOR;
			break;

		case SCALPEL_CODE:
			annotation_name = SCALPEL;
			break;

		case SCISSORS_CODE:
			annotation_name = SCISSORS;
			break;

		case STETHOSCOPE_CODE:
			annotation_name = STETHOSCOPE;
			break;

		case SURGICAL_TAPE_CODE:
			annotation_name = SURGICALTAPE;
			break;

		case SYRINGE_CODE:
			annotation_name = SYRINGE;
			break;

		case TWEEZERS_CODE:
			annotation_name = TWEEZERS;
			break;

		case HAND_POINT_CODE:
			annotation_name = HAND_POINT;
			break;

		case HAND_STRETCH_CODE:
			annotation_name = HAND_STRETCH;
			break;

		case HAND_PALPATE_CODE:
			annotation_name = HAND_PALPATE;
			break;

		case TEXT_CLOSE_CODE:
			annotation_name = TEXT_CLOSE;
			break;

		case TEXT_INCISION_CODE:
			annotation_name = TEXT_INCISION;
			break;

		case TEXT_PALPATION_CODE:
			annotation_name = TEXT_PALPATION;
			break;

		case TEXT_REMOVE_CODE:
			annotation_name = TEXT_REMOVE;
			break;

		case TEXT_STITCH_CODE:
			annotation_name = TEXT_STITCH;
			break;
	}

	return annotation_name;
}

/*
 * Method Overview: Writes a JSON Value to a file
 * Parameters: JSON Value to write
 * Return: None
 */
void JSONManager::writeJSONonFile(Json::Value to_text)
{
	//Opens the file to write in
	file_id.open(JSON_FILE_LOCATION);
	
	//Creates a specialized builder.
	Json::StreamWriterBuilder wbuilder;

	/*
	 * Selects the type of indentation (Tab or no-tab)
	 * The correct way to do it is to use no indentation, but
	 * using tab indentation is an easier way to analyze the
	 * just created json.
	 */
	wbuilder[INDENTATION] = NO_INDENTATION; //TAB_INDENTATION

	//Using the builder, creates a String out of the Json Value 
	std::string string_to_send = Json::writeString(wbuilder, to_text);

	//Writes the string to file
    file_id << string_to_send;

	//Closes the writen file
    file_id.close();

	//Starts the process of sending the value over the network
	JSONtoNetwork(string_to_send);
}

/*
 * Method Overview: Routines to send JSON strings over the network
 * Parameters: String containing the JSON Value
 * Return: None
 */
void JSONManager::JSONtoNetwork(string string_to_send)
{
	//Makes a copy of the string and transform it into a char*
	string my_string_to_send = string_to_send + "\n";
	const char* message_to_send = my_string_to_send.c_str();
	
	//Remove the /**/ when using the ISAT's computer demo client
	//Comment with /**/ when using the tablet client
	//Add or remove the /**/ right before and after the ////////
	///////////////////////////////////////////////////////////////

	//Retrieves info about the message lenght
	int int_message_lenght = strlen(message_to_send);
	stringstream convert;
	convert << int_message_lenght;
	string convert_int_message_lenght = convert.str();
	const char* char_message_lenght = convert_int_message_lenght.c_str();

	//Retrieves info about the lenght of the message lenght
	int int_lenght_message_lenght = strlen(char_message_lenght);
	stringstream convert2;
	convert2 << int_lenght_message_lenght;
	string convert2_int_lenght_message_lenght = convert2.str();
	const char* char_lenght_message_lenght = convert2_int_lenght_message_lenght.c_str();

	//Sends the lenght of the message lenght 
	myCommunicationManager->sendActionPackets(char_lenght_message_lenght,JSON_NETWORK_CODE);

	//Sends the message lenght 
	myCommunicationManager->sendActionPackets(char_message_lenght,JSON_NETWORK_CODE);

	///////////////////////////////////////////////////////////////

	//Actually sends the message
	int iResult = myCommunicationManager->sendActionPackets(message_to_send,JSON_NETWORK_CODE);
	
	//Let the CommanderCenter know that the message was sent
	myCommander->setJSONCreationFlag(0);
}