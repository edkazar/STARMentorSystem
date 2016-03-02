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
 * Name: VideoManager.h
 *
 * Overview: This class uses the OpenCV Library methods and the
 * socket interface previously created to receive a stream of data
 * and reconstruct and image from it. It then applies to that image
 * some geometrical transformations methods. The image then is sent 
 * to the AnnotationManager, the one in charge of drawing it on the
 * screen.
 */
///////////////////////////////////////////////////////////////////

//Define guard
#ifndef VIDEOMANAGER_H
#define VIDEOMANAGER_H

//---------------------------Includes----------------------------//
#include <opencv2/opencv.hpp>//OpenCV Core Libraries
#include "CommandCenter.h"//General Program Flow Controller
#include "CommunicationManager.h"//TCP-IP Socket Server
#include "AnnotationsManager.h"//OpenGL Annotations Manager
#include "GUIManager.h"//Methods used to create the GUI
#include "touchCommands.h"//Touch events standard commands
#include "communicationDefinitions.h"//Socket-related definitions

using namespace cv;//OpenCV Standard

class VideoManager
{
public:
	//-------------------------Methods---------------------------//
	VideoManager(CommunicationManager* server, CommandCenter* pCommander, GUIManager* pGUI);//Class Constructor

	//Apply geometrical transformations based on touch events
	/*CURRENTLY NOT BEING USED*/
	void OpenCVtouchControls(int command, long double x, long double y);

	//Starts the execution of the methods
	void initWindow();

	//------------------------Variables--------------------------//
	//None

private:

	//-------------------------Methods---------------------------//
	//Handles the keyborad received events
	void keyboardInteractions();

	//------------------------Variables--------------------------//
	//Key for keybord inputs
	int key;

	//Received image constants
	int rescamX;
	int rescamY;

	//Screen constants
	int rescompX;
	int rescompY;

	//Determined by the resolution of the screen
	int aspectRatioX;
	int aspectRatioY;

	//Size of the step to translate the image
	int panStep;

	//Zoom scale to multiple the image for
	int zoomScale;

	//Stores the degree the image is being rotated by
	float rotationDegree;

	//Region of interest to be shown on  the screen
	Rect  roi;

	//(xmin,ymin),(xmax,ymax) of the region og interest rectangle
	Point tl,br;

	//Instance of the communication server
	CommunicationManager* myServer;

	//Instance of the GUI creator
	GUIManager* GUIcreator;
};

#endif