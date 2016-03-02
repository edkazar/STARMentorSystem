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
 * Name: MentorSystemMain.cpp
 *
 * Overview: This is the project main. In here, all the required 
 * modules for the proper execution of the application will be
 * initialized. Threads are used to ensure that all the modules
 * will kepp working, regardless the existance of endless loops
 * within them.
 */
///////////////////////////////////////////////////////////////////

//---------------------------Includes----------------------------//
#include "AnnotationsManager.h"//OpenGL Annotations Manager
#include "CommunicationManager.h"//TCP-IP Socket Server
#include "CommandCenter.h"//General Program Flow Controller
#include "GUIManager.h"//Methods used to create the GUI
#include "JSONManager.h"//JSON Type Objects Creator
#include "TouchOverlayController.h"//PQLabs Overlay Controller
#include "VideoManager.h"//OpenCV Video Manager
#include <process.h>//Windows Threads

using namespace std;//Standard Libraries

//---------------------------Modules-----------------------------//
CommandCenter* commander;
CommunicationManager* communicationMan;
GUIManager* GUIMan;
TouchOverlayController touchMan;
VideoManager* videoMan;
JSONManager* JsonMan;

//------Functions used to create the Windows' threads loops------//
void communicationLoop(void *);
void videoLoop(void *);
void JSONLoop(void *);

/*
 * Method Overview: Program main
 * Parameters: Input console commands by the user (if any)
 * Return: whether or not it finished correctly
 */
int main(int argc, char *argv[]) 
{
	int resolutionX = 1920;
	int resolutionY = 1080;

	//init the CommandCenter
	commander = new CommandCenter();

	//CommunicationManager Init
	communicationMan = new CommunicationManager();

	JsonMan = new JSONManager(communicationMan, commander);

	GUIMan = new GUIManager(resolutionX,resolutionY,commander,JsonMan);

	//TouchController Init
	int err_code = touchMan.Init(commander,GUIMan);
	if(err_code != PQMTE_SUCCESS){
		cout << "press any key to exit..." << endl;
		getchar();
		return 0;
	}

	//CommunicationManager Thread Init
	_beginthread( communicationLoop, 0, (void*)12);

	//JSONManager Thread Init
	_beginthread( JSONLoop, 0, (void*)12);

	//VideoManager Init
	videoMan = new VideoManager(communicationMan,commander,GUIMan);

	//VideoManager Thread Init
	_beginthread( videoLoop, 0, (void*)12);

	//AnnotationsManager Init
	//TODO: Replace dims with .txt config file
	initWindow(argc, argv, resolutionX, resolutionY,commander,JsonMan);
	
	return 0;
}

/*
 * Method Overview: Infinite loop for the communication process
 * Parameters: Void array
 * Return: None
 */
void communicationLoop(void * arg) 
{ 
    while(1) 
    {
		//update to accept new clients
		communicationMan->update();
    }
}

/*
 * Method Overview: Inits the OpenCV video capture infinite loop
 * Parameters: Void array
 * Return: None
 */
void videoLoop(void * arg) 
{ 
	//Init the video managing process
	videoMan->initWindow();
}

/*
 * Method Overview: Starts the JSON creation message process
 * Parameters: Void array
 * Return: None
 */
void JSONLoop(void * arg) 
{ 
	//Start the process
	JsonMan->constructGeneralJSON();
}