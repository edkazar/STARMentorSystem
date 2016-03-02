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
 * Name: GUIManager.h
 *
 * Overview: This code uses the OpenCV methods to create a graphic
 * user interface to overlay on top of an image. It checks the 
 * current state of the system to know which images are the ones
 * that should be overlayed.
 */
///////////////////////////////////////////////////////////////////

//Define guards
#ifndef GUIMANAGER_H
#define GUIMANAGER_H

//---------------------------Includes----------------------------//
#include <opencv2/opencv.hpp>//OpenCV Core Library
#include <map>//Enable the usage of the vector class
#include <vector>//Enable the usage of the vector class
#include "CommandCenter.h"//General Program Flow Controller
#include "JSONManager.h"//JSON Type Objects Creator
#include "VirtualAnnotation.h"//Basic Virtual Annotation Structure
#include "touchCommands.h"//Touch events standard commands
#include "GUIDefinitions.h"//Definitions required for the GUI usage
#include "annotationCommands.h"//Annotation-related commands
#include "JSONDefinitions.h"////General JSON definitions
#include "virtualAnnotationDefinitions.h"//Virtual annotation codes

class GUIManager
{
public:
	//-------------------------Methods---------------------------//
	GUIManager(int resX, int resY, CommandCenter* pCommander, JSONManager* pJSON);//Class Constructor

	//Starts the GUI creation process
	cv::Mat createGUI(cv::Mat showImage);

	//Interpretation of whereas or not a button was clicked 
	int clickAnalysis(double posX, double posY);

	//Interpretation of which tool was clicked 
	int touchedAnnotationIdentification(double posX, double posY);

	//Creates and adds a new virtual annotation
	void createVirtualAnnotation(int Id, long double posX, long double posY, int code);

	//returns the Id of the selected annotation (if any)
	int checkAnnotationSelected(long double posX, long double posY);

	//Call functions on a received touch event
	void GUItouchControls(int command);

	//Gives the signal to start the creation of JSON UpdateCommands
	void startJSONAnnotationUpdate();

	//------------------------Variables--------------------------//
	//None

private:
	//-------------------------Methods---------------------------//
	//Inits the images required for the GUI construction
	void initImages();

	//Merges a .png with a .jpg image
	void overlayImage(const cv::Mat &background, const cv::Mat &foreground, cv::Mat &output, cv::Point2i location);
	
	//Overlays all the virtual annotations on top of an image
	cv::Mat overlayAnnotations(cv::Mat GUIImage);

	//Deselect all the existing virtual annotations
	void deselectAllVirtualAnnotations();

	//Erase all the existing virtual annotations
	void clearAllVirtualAnnotations();

	//Erase the selected virtual annotations
	void eraseVirtualAnnotations();

	//Geometrical Transformation: Translate
	void translateVirtualAnnotations(long double amountX, long double amountY);

	//Geometrical Transformation: Zoom
	void zoomVirtualAnnotations(long double zoom);

	//Process by which an annotation is rotated
	void rotateVirtualAnnotations(long double angle);

	//Geometrical transformation: Rotate
	void pointRotation(long double X, long double Y, long double transX,long double transY,
				   long double angle, long double origX, long double origY, long double* rotated_values);

	//Routine to start the JSON creation process
	void createJSONVirtualAnnotationMessage(string command, VirtualAnnotation* annotation);

	//------------------------Variables--------------------------//
	//Matrices to store the button images
	cv::Mat ButtonPointsOn, ButtonPointsOff, ButtonLinesOn, ButtonLinesOff, ButtonClearAll, ButtonErase, ButtonExit;

	//Matrices to store the annotation panels
	cv::Mat AnnotationPanel, AnnotationPanelHidden;

	//Matrices to store the temporal and final results
	cv::Mat tempResult, finalResult;

	//Screen resolution
	int resolutionX, resolutionY;

	//Instance of the general program flow controller
	CommandCenter* myCommander;

	//Stores all the lines that are going to be drawn by Bressenham
	map<int, VirtualAnnotation*> annotationsTable;

	//Stores the Ids of the annotations that are currently selected
	vector<int> selected_annotations_id;

	//Instance of the JSON Manager
	JSONManager* myJSON;
};

#endif