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
 * Name: GUIManager.cpp
 *
 * Overview: .cpp of GUIManager.h
 */
///////////////////////////////////////////////////////////////////

//Include its header file
#include "GUIManager.h"

//--------------------------Definitions--------------------------//
#define PI 3.14159265358979323846

/*
 * Method Overview: Constructor of the class
 * Parameters (1): Resolution of the screen
 * Parameters (2): Instance of the Command Center
 * Parameters (3): Instance of the JSON Manager
 * Return: Instance of the class
 */
GUIManager::GUIManager(int resX, int resY, CommandCenter* pCommander, JSONManager* pJSON)
{
	resolutionX = resX;
	resolutionY = resY;

	//Sets the CommandCenter instance as own
	myCommander = pCommander;

	//Sets the JSONManager instance as own
	myJSON = pJSON;

	//loads the required images
	initImages();
}

/*
 * Method Overview: Overlays the GUI on top of an image
 * Parameters: Image to overlay GUI on top
 * Return: Created GUI Image
 */
cv::Mat GUIManager::createGUI(cv::Mat showImage)
{
	//Overlays the annotations panel tab
	if(!(myCommander->getAnnotationPanelShownFlag()))
	{
		overlayImage(showImage, AnnotationPanelHidden, finalResult, cv::Point(SCREEN_ORIGIN,SCREEN_ORIGIN));
	}
	//Overlays the annotations panel
	else
	{
		overlayImage(showImage, AnnotationPanel, finalResult, cv::Point(SCREEN_ORIGIN,SCREEN_ORIGIN));
	}

	//Overlays the Points Off Button
	if(!(myCommander->getPointsDrawableFlag()))
	{
		overlayImage(finalResult, ButtonPointsOff, tempResult, cv::Point(SCREEN_ORIGIN+ERROR_MARGIN,
			resolutionY-BUTTON_SIZE));
	}
	//Overlays the Points On Button
	else
	{
		overlayImage(finalResult, ButtonPointsOn, tempResult, cv::Point(SCREEN_ORIGIN+ERROR_MARGIN,
			resolutionY-BUTTON_SIZE));
	}

	//Overlays the Lines Off Button
	if(!(myCommander->getLinesDrawableFlag()))
	{
		overlayImage(tempResult, ButtonLinesOff, finalResult, cv::Point(SCREEN_ORIGIN+ERROR_MARGIN+BUTTON_SIZE,
			resolutionY-BUTTON_SIZE));
	}
	//Overlays the Lines On Button
	else
	{
		overlayImage(tempResult, ButtonLinesOn, finalResult, cv::Point(SCREEN_ORIGIN+ERROR_MARGIN+BUTTON_SIZE,
			resolutionY-BUTTON_SIZE));
	}

	//Overlays the Clear All Button
	overlayImage(finalResult, ButtonClearAll, tempResult, cv::Point(resolutionX-BUTTON_SIZE,
		SCREEN_ORIGIN));

	//Overlays the Erase Button
	overlayImage(tempResult, ButtonErase, finalResult, cv::Point(resolutionX-BUTTON_SIZE,
		SCREEN_ORIGIN+BUTTON_SIZE));

	//Overlays the Exit Button
	overlayImage(finalResult, ButtonExit, tempResult, cv::Point(resolutionX-BUTTON_SIZE,
		resolutionY-BUTTON_SIZE));
	
	finalResult = overlayAnnotations(tempResult);

	return finalResult;
}

/*
 * Method Overview: Interprets a performed click event
 * Parameters: X and Y coordinates of the event
 * Return: None
 */
int GUIManager::clickAnalysis(double posX, double posY)
{
	int clicked = 0;

	//Point Button Clicked
	if(posX > POINT_BUTTON_MIN_X && posX < POINT_BUTTON_MAX_X && posY > POINT_BUTTON_MIN_Y && posY < POINT_BUTTON_MAX_Y)
	{
		if(!(myCommander->getPointsDrawableFlag()))
		{
			myCommander->setAnnotationCommandFlag(1);
			myCommander->setAnnotationCommand(DESELECT_ALL_LINES);
			myCommander->setPointsDrawableFlag(1);

			deselectAllVirtualAnnotations();	
		}
		else
		{
			myCommander->setPointsDrawableFlag(0);
		}
		myCommander->setLinesDrawableFlag(0);
		clicked = 1;
	}
	//Line Button Clicked
	else if(posX > LINE_BUTTON_MIN_X && posX < LINE_BUTTON_MAX_X && posY > LINE_BUTTON_MIN_Y && posY < LINE_BUTTON_MAX_Y)
	{
		if(!(myCommander->getLinesDrawableFlag()))
		{
			myCommander->setAnnotationCommandFlag(1);
			myCommander->setAnnotationCommand(DESELECT_ALL_LINES);
			myCommander->setLinesDrawableFlag(1);

			deselectAllVirtualAnnotations();
		}
		else
		{
			myCommander->setLinesDrawableFlag(0);
		}
		myCommander->setPointsDrawableFlag(0);
		clicked = 1;
	}
	//Clear All Button Clicked
	else if(posX > CLEAR_BUTTON_MIN_X && posX < CLEAR_BUTTON_MAX_X && posY > CLEAR_BUTTON_MIN_Y && posY < CLEAR_BUTTON_MAX_Y)
	{
		myCommander->setAnnotationCommand(CLEAR_ALL_LINES);
		clearAllVirtualAnnotations();
		clicked = 1;
	}
	//Erase Button Clicked
	else if(posX > ERASE_BUTTON_MIN_X && posX < ERASE_BUTTON_MAX_X && posY > ERASE_BUTTON_MIN_Y && posY < ERASE_BUTTON_MAX_Y)
	{
		
		myCommander->setAnnotationCommand(ERASE_LINES);
		eraseVirtualAnnotations();
		clicked = 1;
	}
	//Exit Button Clicked
	else if(posX > EXIT_BUTTON_MIN_X && posX < EXIT_BUTTON_MAX_X && posY > EXIT_BUTTON_MIN_Y && posY < EXIT_BUTTON_MAX_Y)
	{
		myCommander->setAnnotationCommandFlag(1);
		myCommander->setAnnotationCommand(END_OPENGL_CONTEXT);
	}

	//if the annotation panel is being shown
	if(myCommander->getAnnotationPanelShownFlag())
	{
		//Open Panel Tab Clicked
		if(posX > OPEN_PANEL_TAB_MIN_X && posX < OPEN_PANEL_TAB_MAX_X && 
			posY > OPEN_PANEL_TAB_MIN_Y && posY < OPEN_PANEL_TAB_MAX_Y)
		{
			myCommander->setAnnotationPanelShownFlag(0);
			myCommander->setLinesDrawableFlag(0);
			myCommander->setPointsDrawableFlag(0);
			clicked = 1;
		}
	}
	else
	{
		//Closed Panel Tab Clicked
		if(posX > CLOSED_PANEL_TAB_MIN_X && posX < CLOSED_PANEL_TAB_MAX_X && 
			posY > CLOSED_PANEL_TAB_MIN_Y && posY < CLOSED_PANEL_TAB_MAX_Y)
		{
			myCommander->setAnnotationPanelShownFlag(1);
			myCommander->setLinesDrawableFlag(0);
			myCommander->setPointsDrawableFlag(0);
			clicked = 1;
		}
	}

	return clicked;
}

/*
 * Method Overview: Finds which annotation of the panel was touched
 * Parameters: X and Y coordinates of the event
 * Return: Code of the touched annotation
 */
int GUIManager::touchedAnnotationIdentification(double posX, double posY)
{
	int code;

	//Determines which row was clicked
	if(posY>FIRST_ROW_UPPER_MARGIN && posY<FIRST_ROW_LOWER_MARGIN)
	{
		code = FIRST_ROW_CODE;
	}
	else if(posY>SECOND_ROW_UPPER_MARGIN && posY<SECOND_ROW_LOWER_MARGIN)
	{
		code = SECOND_ROW_CODE;
	}
	else if(posY>THIRD_ROW_UPPER_MARGIN && posY<THIRD_ROW_LOWER_MARGIN)
	{
		code = THIRD_ROW_CODE;
	}
	else if(posY>FOURTH_ROW_UPPER_MARGIN && posY<FOURTH_ROW_LOWER_MARGIN)
	{
		code = FOURTH_ROW_CODE;
	}
	else if(posY>FIFTH_ROW_UPPER_MARGIN && posY<FIFTH_ROW_LOWER_MARGIN)
	{
		code = FIFTH_ROW_CODE;
	}
	else if(posY>SIXTH_ROW_UPPER_MARGIN && posY<SIXTH_ROW_LOWER_MARGIN)
	{
		code = SIXTH_ROW_CODE;
	}
	else if(posY>SEVENTH_ROW_UPPER_MARGIN && posY<SEVENTH_ROW_LOWER_MARGIN)
	{
		code = SEVENTH_ROW_CODE;
	}

	//Determines which column was clicked
	if(posX>FIRST_COLUMN_LEFT_MARGIN && posX<FIRST_COLUMN_RIGHT_MARGIN)
	{
		code *= FIRST_COLUMN_CODE;
	}
	else if(posX>SECOND_COLUMN_LEFT_MARGIN && posX<SECOND_COLUMN_RIGHT_MARGIN)
	{
		code *= SECOND_COLUMN_CODE;
	}
	else if(posX>THIRD_COLUMN_LEFT_MARGIN && posX<THIRD_COLUMN_RIGHT_MARGIN)
	{
		code *= THIRD_COLUMN_CODE;
	}

	return code;
}

/*
 * Method Overview: Creates a new virtual annotation
 * Parameters: Id, code and coordinates of the new tool
 * Return: None
 */
void GUIManager::createVirtualAnnotation(int Id, long double posX, long double posY, int code)
{
	VirtualAnnotation* new_annotation = new VirtualAnnotation(Id, posX, posY, code);

	selected_annotations_id.push_back(Id);

	myCommander->setVirtualAnnotationSelectedFlag(1);

	annotationsTable.insert(pair<int, VirtualAnnotation*>(Id,new_annotation));

	createJSONVirtualAnnotationMessage(CREATE_ANNOTATION_COMMAND, new_annotation);
}

/*
 * Method Overview: Searches if an virtual annotation was clicked
 * Parameters: (X,Y) coordinates of the point clicked
 * Return: Id of the clicked annotation
 */
int GUIManager::checkAnnotationSelected(long double posX, long double posY)
{
	deselectAllVirtualAnnotations();

	int annotation_id = -1;

	//Iterator to go through the map
    std::map<int, VirtualAnnotation*>::iterator iter;
	
	//Loops through all the lines
    for (iter = annotationsTable.begin(); iter != annotationsTable.end(); iter++)
    {
		VirtualAnnotation* annotation = iter->second;

		if(posX > annotation->getExtremePoints()[0] && posX < annotation->getExtremePoints()[2] 
		&& posY > annotation->getExtremePoints()[1] && posY < annotation->getExtremePoints()[3])
		{
			if(annotation->checkPixelTransparency(posX,posY))
			{
				annotation_id = annotation->getID();
				selected_annotations_id.push_back(annotation_id);
				annotation->setSelectedState(1);
				myCommander->setVirtualAnnotationSelectedFlag(1);
				myCommander->setLineSelectedFlag(0);

				myCommander->setAnnotationCommandFlag(1);
				myCommander->setAnnotationCommand(DESELECT_ALL_LINES);

				break;
			}
		}
	}

	return annotation_id;
}

/*
 * Method Overview: Touch events handling
 * Parameters: Received action
 * Return: None
 */
void GUIManager::GUItouchControls(int command)
{
	//analyzes which event occured
    switch (command)
    {	
		//Rotations
		//rotate counterclockwise
		case ROTATE_CNTR_CLK:
			rotateVirtualAnnotations(-2.0f);
			break;

		//rotate clockwise
		case ROTATE_CLK:
			rotateVirtualAnnotations(2.0f);
			break;

		//Zooms
		//zoom in
		case ZOOM_IN:
			zoomVirtualAnnotations(1.2f);
			break;

		//zoom out
		case ZOOM_OUT:
			zoomVirtualAnnotations(0.8f);
			break;

		//Pans
		//right pan
		case TRANSLATE_RIGHT:
			translateVirtualAnnotations(resolutionX/50.0f,0);
			break;

		//left pan
		case TRANSLATE_LEFT:
			translateVirtualAnnotations(-resolutionX/50.0f,0);
			break;

		//up pan
		case TRANSLATE_UP:
			translateVirtualAnnotations(0,-resolutionY/50.0f);
			break;

		//down pan
		case TRANSLATE_DOWN:
			translateVirtualAnnotations(0,resolutionY/50.0f);
			break;
	}
}

/*
 * Method Overview: Starts the JSON Update process
 * Parameters: None
 * Return: None
 */
void GUIManager::startJSONAnnotationUpdate()
{
	int i;

	//Loop through all the lines
	for (i = 0; i < (int)selected_annotations_id.size(); i++) 
	{
		VirtualAnnotation* selected = annotationsTable.find(selected_annotations_id.at(i))->second;

		createJSONVirtualAnnotationMessage(UPDATE_ANNOTATION_COMMAND, selected);
	}
}

/*
 * Method Overview: Loads the images used during the GUI process
 * Parameters: None
 * Return: None
 */
void GUIManager::initImages()
{
	ButtonPointsOn = cv::imread(BUTTON_POINTS_ON_PATH,-1);
	ButtonPointsOff = cv::imread(BUTTON_POINTS_OFF_PATH,-1);
	ButtonLinesOn = cv::imread(BUTTON_LINES_ON_PATH,-1);
	ButtonLinesOff = cv::imread(BUTTON_LINES_OFF_PATH,-1);
	ButtonClearAll = cv::imread(BUTTON_CLEAR_PATH,-1);
	ButtonErase = cv::imread(BUTTON_ERASE_PATH,-1);
	ButtonExit = cv::imread(BUTTON_EXIT_PATH,-1);
	AnnotationPanel = cv::imread(ANNOTATION_PANEL_PATH,-1);
	AnnotationPanelHidden = cv::imread(ANNOTATION_PANEL_HIDDEN_PATH,-1);
}

/*
 * Method Overview: Overlays an .png on top of a received image
 * Parameters (1): Background, foreground and result images
 * Parameters (2): Coordinates to place the foreground in
 * Return: None
 */
void GUIManager::overlayImage(const cv::Mat &background, const cv::Mat &foreground, cv::Mat &output, cv::Point2i location)
{
	background.copyTo(output);

	// start at the row indicated by location, or at row 0 if location.y is negative.
	for(int y = max(location.y , 0); y < background.rows; ++y)
	{
		int fY = y - location.y; // because of the translation

		// we are done of we have processed all rows of the foreground image.
		if(fY >= foreground.rows)
			break;

		// start at the column indicated by location, 

		// or at column 0 if location.x is negative.
		for(int x = max(location.x, 0); x < background.cols; ++x)
		{
			int fX = x - location.x; // because of the translation.

			// we are done with this row if the column is outside of the foreground image.
			if(fX >= foreground.cols)
				break;

			// determine the opacity of the foregrond pixel, using its fourth (alpha) channel.
			double opacity =((double)foreground.data[fY * foreground.step + 
				fX * foreground.channels() + 3])/ 255.;


			// and now combine the background and foreground pixel, using the opacity, 

			// but only if opacity > 0.
			for(int c = 0; opacity > 0 && c < output.channels(); ++c)
			{
				unsigned char foregroundPx =
					foreground.data[fY * foreground.step + fX * foreground.channels() + c];

				unsigned char backgroundPx = 
					background.data[y * background.step + x * background.channels() + c];
				output.data[y*output.step + output.channels()*x + c] = 
					(unsigned char)(backgroundPx * (1.-opacity) + foregroundPx * opacity);
			}
		}
	}
}

/*
 * Method Overview: Overlays virtual annotations on top the GUI
 * Parameters: GUI image
 * Return: GUI image with overlayed annotations
 */
cv::Mat GUIManager::overlayAnnotations(cv::Mat GUIImage)
{
	cv::Mat tempResult = GUIImage;
	cv::Mat finalResult = GUIImage;
	long double coordinateX, coordinateY;

	cv::Mat image_to_show;

	int is_temp = 0;

	//Iterator to go through the map
    std::map<int, VirtualAnnotation*>::iterator iter;
	
	//Loops through all the annotations
    for (iter = annotationsTable.begin(); iter != annotationsTable.end(); iter++)
    {
		is_temp = !is_temp;

		coordinateX = (iter->second->getExtremePoints()[0]);
		coordinateY = (iter->second->getExtremePoints()[3]);
		image_to_show = iter->second->imageRotation(iter->second->getImage());

		int timer;
		for(timer=0;timer<250;timer++)
		{

		}

		if(is_temp)
		{
			overlayImage(finalResult,image_to_show, tempResult, cv::Point((int)coordinateX, 
				resolutionY-(int)coordinateY));
		}
		else
		{
			overlayImage(tempResult, image_to_show, finalResult, cv::Point((int)coordinateX, 
				resolutionY-(int)coordinateY));
		}
	}
	
	//after looping through all the virtual annotations
	if(is_temp)
	{
		return tempResult;
	}
	else
	{
		return finalResult;
	}
}

/*
 * Method Overview: Deselects all the virtual annotations
 * Parameters: None
 * Return: None
 */
void GUIManager::deselectAllVirtualAnnotations()
{
	//Iterator to go through the map
    std::map<int, VirtualAnnotation*>::iterator iter;
	
	//Loops through all the lines
    for (iter = annotationsTable.begin(); iter != annotationsTable.end(); iter++)
    {
		iter->second->setSelectedState(0);
	}

	selected_annotations_id.clear();

	myCommander->setVirtualAnnotationSelectedFlag(0);
}

/*
 * Method Overview: Deselects all the virtual annotations
 * Parameters: None
 * Return: None
 */
void GUIManager::eraseVirtualAnnotations()
{
	int counter;

	//Loop through all the lines
	for (counter = 0; counter < (int)selected_annotations_id.size(); counter++) 
	{
		annotationsTable.erase(selected_annotations_id.at(counter));
	}

	myCommander->setSelectedIDs(selected_annotations_id);
	myCommander->setAnnotationCommandFlag(1);

	selected_annotations_id.clear();
}

/*
 * Method Overview: Clears all the virtual annotations
 * Parameters: None
 * Return: None
 */
void GUIManager::clearAllVirtualAnnotations()
{
	selected_annotations_id.clear();

	//Iterator to go through the map
    std::map<int, VirtualAnnotation*>::iterator iter;
	
	//Loops through all the lines
    for (iter = annotationsTable.begin(); iter != annotationsTable.end(); iter++)
    {
		selected_annotations_id.push_back(iter->second->getID());
    }

	eraseVirtualAnnotations();
}

/*
 * Method Overview: Translates annotations by an specific amount
 * Parameters: X and Y translation amounts
 * Return: None
 */
void GUIManager::translateVirtualAnnotations(long double amountX, long double amountY)
{
	int i;

	//Loop through all the lines
	for (i = 0; i < (int)selected_annotations_id.size(); i++) 
	{
		VirtualAnnotation* to_transf = annotationsTable.find(selected_annotations_id.at(i))->second;

		//changs the extreme values of the line
		(to_transf->getExtremePoints())[0] += amountX;
		(to_transf->getExtremePoints())[1] += amountY;
		(to_transf->getExtremePoints())[2] += amountX;
		(to_transf->getExtremePoints())[3] += amountY;

		//calls the function to recalculate the center
		to_transf->recalculateCenter();
	}
}

/*
 * Method Overview: Zooms annotations by an specific amount
 * Parameters: Zoom amounts
 * Return: None
 */
void GUIManager::zoomVirtualAnnotations(long double zoom)
{
	int i;

	//Loop through all the lines
	for (i = 0; i < (int)selected_annotations_id.size(); i++) 
	{
		VirtualAnnotation* to_transf = annotationsTable.find(selected_annotations_id.at(i))->second;

		to_transf->modifyZoomValue(zoom);

		//changes the extreme values of the annotation
		(to_transf->getExtremePoints())[0] = (((to_transf->getExtremePoints())[0] - 
			(to_transf->getAnnotationCenter()[0]))*zoom)+(to_transf->getAnnotationCenter()[0]);
		(to_transf->getExtremePoints())[1] = (((to_transf->getExtremePoints())[1] - 
			(to_transf->getAnnotationCenter()[1]))*zoom)+(to_transf->getAnnotationCenter()[1]);
		(to_transf->getExtremePoints())[2] = (((to_transf->getExtremePoints())[2] - 
			(to_transf->getAnnotationCenter()[0]))*zoom)+(to_transf->getAnnotationCenter()[0]);
		(to_transf->getExtremePoints())[3] = (((to_transf->getExtremePoints())[3] - 
			(to_transf->getAnnotationCenter()[1]))*zoom)+(to_transf->getAnnotationCenter()[1]);

		//calls the function to recalculate the center
		to_transf->recalculateCenter();
	}
}

/*
 * Method Overview: Rotates annotations by an specific amount
 * Parameters: Rotation amount
 * Return: None
 */
void GUIManager::rotateVirtualAnnotations(long double angle)
{
	int i;

	//Loop through all the lines
	for (i = 0; i < (int)selected_annotations_id.size(); i++) 
	{
		VirtualAnnotation* to_transf = annotationsTable.find(selected_annotations_id.at(i))->second;
		
		to_transf->modifyRotationValue(angle);
	}
}

/*
 * Method Overview: Rotates an specific point
 * Parameters (1): Point to rotate, distance to the center
 * Parameters (2): Angle to rotate, point to rotate around off
 * Parameters (3): Array with the rotated values
 * Return: None
 */
void GUIManager::pointRotation(long double X, long double Y, long double transX,long double transY,
				   long double angle, long double origX, long double origY, long double* rotated_values)
{
	//Variables used during the process
	long double xtransf0, ytransf0, cosx0, senx0, cosy0, seny0;

	//Translates the point to the center of the scene
	xtransf0 = (X + transX) - (origX);
	ytransf0 = (Y + transY) - (origY);

	//Calculates trigonometric values of the point
	cosx0 = cos(angle)*xtransf0;
	senx0 = sin(angle)*xtransf0;
	cosy0 = cos(angle)*ytransf0;
	seny0 = sin(angle)*ytransf0;

	//Calculates the new point
	xtransf0 = ((cosx0) - (seny0));
	ytransf0 = ((senx0) + (cosy0));

	rotated_values[0] = (xtransf0)+(origX);
	rotated_values[1] = (ytransf0)+(origY);	
}

/*
 * Method Overview: Uses the JSONManager to create a JSON Message
 * Parameters: Message command, annotation to make the massage from
 * Return: None
 */
void GUIManager::createJSONVirtualAnnotationMessage(string command, VirtualAnnotation* annotation)
{
	vector<double> annotation_information;

	annotation_information.push_back((double)annotation->getAnnotationCenter()[0]);
	annotation_information.push_back((double)annotation->getAnnotationCenter()[1]);
	annotation_information.push_back((double)annotation->getRotationValue());
	annotation_information.push_back((double)annotation->getZoomValue());

	vector<long double> null_double_vector;
	vector<int> null_int_vector;
	myJSON->createJSONable(annotation->getID(), command, &null_double_vector, annotation->getCode(),
		annotation_information, null_int_vector);
}