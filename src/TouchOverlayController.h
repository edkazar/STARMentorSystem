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
 * Name: TouchOverlayController.h
 *
 * Overview: This class uses the PQLabs Touch Overlay SDK to create
 * a simple touch event handler. Each generated touch event will be
 * received and analyzed by this code, which will call the class to
 * handle the event. The code was edited from the PQLabs MultiTouch
 * Client Sample code, created on 12/19/2008 and available for
 * download from their homepage: http://multitouch.com/sdk.html
 */
///////////////////////////////////////////////////////////////////

//Define guard
#ifndef TOUCH_OVERLAY_CONTROLLER_H
#define TOUCH_OVERLAY_CONTROLLER_H

//---------------------------Includes----------------------------//
#include <iostream>//Input/Output Functions
#include <sstream>//String Stream Functions
#include <vector>////Enable the usage of the vector class
#include "PQMTClient.h"//PQLabs Libraries
#include "CommandCenter.h"//General Program Flow Controller
#include "AnnotationsManager.h"//OpenGL Annotations Manager
#include "GUIManager.h"//Methods used to create the GUI
#include "GUIDefinitions.h"//Definitions required for the GUI usage
#include "touchCommands.h"//Touch events standard commands

using namespace std;//Standard Libraries

//PQLabs SDK Libraries
using namespace PQ_SDK_MultiTouch;

//Enables the usage  of the PBLabs Overlay Libraries
#pragma comment(lib,"PQMTClient.lib")

class TouchOverlayController
{
public:
	//-------------------------Methods---------------------------//
	TouchOverlayController();//Class Constructor

	~TouchOverlayController();//Class Destructor

	//Starts the internal variables of the controller
	int Init(CommandCenter* pCommander, GUIManager* pGUI);

	//------------------------Variables--------------------------//
	//Instance of the CommanderCenter
	static CommandCenter* myCommander;

	//Instance of the GUIManager
	static GUIManager* myGUI;
	
private:
	//-------------------------Methods---------------------------//
		//----------------Call Back Methods------------------//
	//Method to handle when recieve touch point frame
	static void OnReceivePointFrame(int frame_id,int time_stamp,int moving_point_count,const TouchPoint * moving_point_array, void * call_back_object);

	//Method to handle when recieve touch gesture
	static void OnReceiveGesture(const TouchGesture & ges, void * call_back_object);

	//Method to handle when server break
	static void OnServerBreak(void * param, void * call_back_object);

	//Method to handle touch data receiving errors
	static void OnReceiveError(int err_code,void * call_back_object);

	//Method to get the resolution of the server system
	static void OnGetServerResolution(int x, int y, void * call_back_object);

	//Method to get the information of the touch device
	static void OnGetDeviceInfo(const TouchDeviceInfo & device_info, void * call_back_object);

		//--------------Touch Gesture Methods----------------//

	//Init the TouchGestures handling methods
	void InitFuncOnTG();

	//Set the call back methods while reciving touch data
	void SetFuncsOnReceiveProc();

	//Method to handle TouchPoint
	//void OnTouchPoint(const TouchPoint & tp);

	//Method to handle TouchGesture
	void OnTouchGesture(const TouchGesture & tg);

	//Use method pointer table to handle the different gesture type
	typedef void (*PFuncOnTouchGesture)(const TouchGesture & tg,void * call_object);

	//Metthod to handle a default touch gesture event
	//static void DefaultOnTG(const TouchGesture & tg,void * call_object);

	//Method to handle the Touch Start event
	static void OnTG_TouchStart(const TouchGesture & tg,void * call_object);

	//Method to handle the Touch Down event
	static void OnTG_Down(const TouchGesture & tg,void * call_object);

	//Method to handle the Touch Move event
	//static void OnTG_Move(const TouchGesture & tg,void * call_object);

	//Method to handle the Touch Up event
	//static void OnTG_Up(const TouchGesture & tg,void * call_object);
		
	//Method to handle the Second Down event
	//static void OnTG_SecondDown(const TouchGesture & tg,void * call_object);

	//Method to handle the Second Up event
	//static void OnTG_SecondUp(const TouchGesture & tg,void * call_object);

	//Method to handle the Click event
	static void OnTG_Click(const TouchGesture & tg,void * call_object);

	//Method to handle the Move Right event
	static void OnTG_MoveRight(const TouchGesture & tg,void * call_object);

	//Method to handle the Move Left event
	static void OnTG_MoveLeft(const TouchGesture & tg,void * call_object);

	//Method to handle the Move Down event
	static void OnTG_MoveDown(const TouchGesture & tg,void * call_object);

	//Method to handle the Move Up event
	static void OnTG_MoveUp(const TouchGesture & tg,void * call_object);

	//Method to handle the Touch End event
	static void OnTG_TouchEnd(const TouchGesture & tg,void * call_object);

	//Method to handle the Rotate Clockwise event
	static void OnTG_RotateClock(const TouchGesture & tg,void * call_object);

	//Method to handle the Rotate CounterClockwise event
	static void OnTG_RotateAntiClock(const TouchGesture & tg,void * call_object);

	//Method to handle the Split Start event
	//static void OnTG_SplitStart(const TouchGesture & tg,void * call_object);

	//Method to handle the Split Apart event
	static void OnTG_SplitApart(const TouchGesture & tg,void * call_object);

	//Method to handle the Split Close event
	static void OnTG_SplitClose(const TouchGesture & tg,void * call_object);

	//Method to handle the Split End event
	//static void OnTG_SplitEnd(const TouchGesture & tg,void * call_object);

	//Method to handle the Parrell Move Up event
	static void onTG_NearParrellMoveUp(const TouchGesture & tg,void * call_object);

	//Method to handle the Parrell Move Down event
	static void onTG_NearParrellMoveDown(const TouchGesture & tg,void * call_object);

	//Method to handle the Parrell Move Right event
	static void onTG_NearParrellMoveRight(const TouchGesture & tg,void * call_object);

	//Method to handle the Parrell Move Left event
	static void onTG_NearParrellMoveLeft(const TouchGesture & tg,void * call_object);

	//------------------------Variables--------------------------//
	//min-max values of the touched drawn region (if any)
	static vector<long double> roi_extremes;

	//Counts how many lines have been created
	static int annotationCounter;

	//Stores the code of the selected virtual annotation
	static int selected_annotation_code;

	//Touch gesture pointer table
	PFuncOnTouchGesture m_pf_on_tges[TG_TOUCH_END + 1];

	static unsigned short last_type;

};// sample code end

#endif // end of header