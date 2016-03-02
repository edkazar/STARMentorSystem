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
 * Name: JSONManager.h
 *
 * Overview: This class uses the Json library created by Baptiste
 * Lepilleur (see json.h for details of it) to create a series of 
 * messages to be sent to a client. Those messages will contain the
 * required information about the annotations (either virtual or
 * line type) and will be then send to the CommunicationManager for
 * it to send the messages over the network.
 */
///////////////////////////////////////////////////////////////////

//Define guard
#ifndef JSONMANAGER_H
#define JSONMANAGER_H

//---------------------------Includes----------------------------//
#include <queue>//Queue Data Structure
#include <fstream>//Enables the code to read and write an file
#include "json.h"//Baptiste Lepilleur's JSON c++ Library
#include "CommandCenter.h"//General Program Flow Controller
#include "CommunicationManager.h"//TCP-IP Socket Server
#include "JSONDefinitions.h"////General JSON definitions
#include "virtualAnnotationDefinitions.h"//Virtual annotation codes
#include "communicationDefinitions.h"//Socket-related definitions

class JSONManager
{
public:

	struct JSONable
	{
		int id;
		string command;
		vector<long double>* myPoints;
		int annotation_code;
		vector<double> annotation_information;
		vector<int> selected_annotation_id;
	};

	//-------------------------Methods---------------------------//
	JSONManager(CommunicationManager* pManager, CommandCenter* pCommand);//Class Constructor

	//loop to create the JSON messages
	void constructGeneralJSON();

	//create a object that will be transformed to a JSON later on
	void createJSONable(int id, string command, vector<long double>* myPoints, int annotation_code, 
		vector<double> annotation_information, vector<int> selected_annotation_id);		

	//------------------------Variables--------------------------//
	//None

private:
	//-------------------------Methods---------------------------//
	//Finds the annotation name out if its specific code
	string findAnnotationName(int code);

	//Prepares a Json Value of a line to be sent
	void constructLineJSONMessage(int id, string command, vector<long double>* myPoints);

	//Prepares a Json Value of a virtual annotation to be sent
	void constructVirtualAnnotationJSONMessage(int id, string command, int annotation_code, vector<double> annotation_information);

	//Prepares a Json Value of a delete command
	void constructDeleteJSONMessage(string command, vector<int> selected_annotation_id);

	//Writes a created JSON Value to a file
	void JSONManager::writeJSONonFile(Json::Value to_text);

	//Starts the process of sending a JSON string over the network
	void JSONtoNetwork(string string_to_send);

	//------------------------Variables--------------------------//
	//Instance of the general program flow controller
	CommandCenter* myCommander;
	
	//Instance of the Communication Manager
	CommunicationManager* myCommunicationManager;

	//Used to open and save the JSON Value in a file
	std::ofstream file_id;

	//Queue structure used to store the JSON-to-create information
	std::queue<JSONable> JSONs_to_create;
};
#endif