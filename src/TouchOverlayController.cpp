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
 * Name: TouchOverlayController.cpp
 *
 * Overview: .cpp of TouchOverlayController.h
 */
///////////////////////////////////////////////////////////////////

//Include its header file
#include "TouchOverlayController.h"

//--------------------------Definitions--------------------------//
#define BIG_VALUE 10000
#define SMALL_VALUE -10000

//--------------------------Variables----------------------------//
CommandCenter* TouchOverlayController::myCommander;
GUIManager* TouchOverlayController::myGUI;
int TouchOverlayController::annotationCounter;
int TouchOverlayController::selected_annotation_code;
vector<long double> TouchOverlayController::roi_extremes;
unsigned short TouchOverlayController::last_type;

/*
 * Method Overview: Constructor of the class
 * Parameters: None 
 * Return: Instance of the class
 */
TouchOverlayController::TouchOverlayController()
{
	annotationCounter = 0;
	roi_extremes.push_back(0.0);
	memset(m_pf_on_tges,0, sizeof(m_pf_on_tges));
}

/*
 * Method Overview: Destructor of the class
 * Parameters: None
 * Return: None
 */
TouchOverlayController::~TouchOverlayController()
{
	DisconnectServer();
}

/*
 * Method Overview: Starts the Touch Overlay Controller
 * Parameters (1): Instance of the Communication Manager server
 * Parameters (2): Instance of the Command Center
 * Return: flag of successfulness
 */
int TouchOverlayController::Init(CommandCenter* pCommander, GUIManager* pGUI)
{
	//Sets the CommandCenter instance as own
	myCommander = pCommander;

	//Establishes the GUIManager
	myGUI = pGUI;

	//Successful Init
	int err_code = PQMTE_SUCCESS;

	//Initialize the handle functions of gestures;
	InitFuncOnTG();

	//Set the functions on server callback
	SetFuncsOnReceiveProc();

	//Connect server
	cout << " connect to server..." << endl;
	if((err_code = ConnectServer()) != PQMTE_SUCCESS){
		cout << " connect server fail, socket error code:" << err_code << endl;
		return err_code;
	}
	// send request to server
	cout << " connect success, send request." << endl;
	TouchClientRequest tcq = {0};
	tcq.type = RQST_RAWDATA_ALL | RQST_GESTURE_ALL;
	if((err_code = SendRequest(tcq)) != PQMTE_SUCCESS){
		cout << " send request fail, error code:" << err_code << endl;
		return err_code;
	}

	//get server resolution
	if((err_code = GetServerResolution(OnGetServerResolution, NULL)) != PQMTE_SUCCESS){
		cout << " get server resolution fail,error code:" << err_code << endl;
		return err_code;
	}
	
	// start receiving
	cout << " send request success, start recv." << endl;
	return err_code;
}

/*
 * Method Overview: Init the Touch Gestures methods handlers
 * Parameters: None
 * Return: None
 */
void TouchOverlayController:: InitFuncOnTG()
{
	/*
	 * Some handlers are not used. However, they could be useful
	 * later on. Therefore, they were commented instead of deleted
	 */

	m_pf_on_tges[TG_TOUCH_START] = &TouchOverlayController::OnTG_TouchStart;
	m_pf_on_tges[TG_DOWN] = &TouchOverlayController::OnTG_Down;
	//m_pf_on_tges[TG_MOVE] = &TouchOverlayController::OnTG_Move;
	//m_pf_on_tges[TG_UP] = &TouchOverlayController::OnTG_Up;
	m_pf_on_tges[TG_CLICK] = &TouchOverlayController::OnTG_Click;

	//m_pf_on_tges[TG_SECOND_DOWN] = &TouchOverlayController::OnTG_SecondDown;
	//m_pf_on_tges[TG_SECOND_UP] = &TouchOverlayController::OnTG_SecondUp;

	m_pf_on_tges[TG_MOVE_RIGHT] = &TouchOverlayController::OnTG_MoveRight;
	m_pf_on_tges[TG_MOVE_LEFT] = &TouchOverlayController::OnTG_MoveLeft;
	m_pf_on_tges[TG_MOVE_DOWN] = &TouchOverlayController::OnTG_MoveDown;
	m_pf_on_tges[TG_MOVE_UP] = &TouchOverlayController::OnTG_MoveUp;

	m_pf_on_tges[TG_TOUCH_END] = &TouchOverlayController::OnTG_TouchEnd;
	
	m_pf_on_tges[TG_ROTATE_CLOCK] = &TouchOverlayController::OnTG_RotateClock;
	m_pf_on_tges[TG_ROTATE_ANTICLOCK] = &TouchOverlayController::OnTG_RotateAntiClock;
	//m_pf_on_tges[TG_SPLIT_START] = &TouchOverlayController::OnTG_SplitStart;
	m_pf_on_tges[TG_SPLIT_APART] = &TouchOverlayController::OnTG_SplitApart;
	m_pf_on_tges[TG_SPLIT_CLOSE] = &TouchOverlayController::OnTG_SplitClose;
	//m_pf_on_tges[TG_SPLIT_END] = &TouchOverlayController::OnTG_SplitEnd;
	m_pf_on_tges[TG_NEAR_PARREL_MOVE_UP] = &TouchOverlayController::onTG_NearParrellMoveUp;
	m_pf_on_tges[TG_NEAR_PARREL_MOVE_DOWN] = &TouchOverlayController::onTG_NearParrellMoveDown;
	m_pf_on_tges[TG_NEAR_PARREL_MOVE_RIGHT] = &TouchOverlayController::onTG_NearParrellMoveRight;
	m_pf_on_tges[TG_NEAR_PARREL_MOVE_LEFT] = &TouchOverlayController::onTG_NearParrellMoveLeft;
}

/*
 * Method Overview: Init the call back methods handlers
 * Parameters: None
 * Return: None
 */
void TouchOverlayController::SetFuncsOnReceiveProc()
{
	PFuncOnReceivePointFrame old_rf_func = SetOnReceivePointFrame(&TouchOverlayController::OnReceivePointFrame,this);
	PFuncOnReceiveGesture old_rg_func = SetOnReceiveGesture(&TouchOverlayController::OnReceiveGesture,this);
	PFuncOnServerBreak old_svr_break = SetOnServerBreak(&TouchOverlayController::OnServerBreak,NULL);
	PFuncOnReceiveError old_rcv_err_func = SetOnReceiveError(&TouchOverlayController::OnReceiveError,NULL);
	PFuncOnGetDeviceInfo old_gdi_func = SetOnGetDeviceInfo(&TouchOverlayController::OnGetDeviceInfo,NULL);
}

/*
 * Method Overview: Handles the reception of touch point frames
 * Parameters (1): Point frame, time stamp of the event
 * Parameters (2): Count of how many points are moving
 * Parameters (3): Array to store the moving points
 * Parameters (4): Object that created the call back event
 * Return: None
 */
void TouchOverlayController:: OnReceivePointFrame(int frame_id, int time_stamp, int moving_point_count, const TouchPoint * moving_point_array, void * call_back_object)
{
	TouchOverlayController * controller = static_cast<TouchOverlayController*>(call_back_object);
	assert(controller != NULL);
	const char * tp_event[] = 
	{
		"down",
		"move",
		"up",
	};
	
	//cout << " frame_id:" << frame_id << " time:"  << time_stamp << " ms" << " moving point count:" << moving_point_count << endl;
	for(int i = 0; i < moving_point_count; ++ i){
		TouchPoint tp = moving_point_array[i];
		//controller->OnTouchPoint(tp); //Enable if this handler is needed
	}
}

/*
 * Method Overview: Handles the reception of touch gestures
 * Parameters (1): Received gesture
 * Parameters (2): Object that created the call back event
 * Return: None
 */
void TouchOverlayController:: OnReceiveGesture(const TouchGesture & ges, void * call_back_object)
{
	TouchOverlayController * controller = static_cast<TouchOverlayController*>(call_back_object);
	assert(controller != NULL);
	controller->OnTouchGesture(ges);
	//throw exception("test exception here");
}

/*
 * Method Overview: Handles server break event
 * Parameters (1): Server break parameter
 * Parameters (2): Object that created the call back event
 * Return: None
 */
void TouchOverlayController:: OnServerBreak(void * param, void * call_back_object)
{
	// when the server break, disconenct server;
	cout << "server break, disconnect here" << endl;
	DisconnectServer();
}

/*
 * Method Overview: Handles error event
 * Parameters (1): Server break parameter
 * Parameters (2): Object that created the call back event
 * Return: None
 */
void TouchOverlayController::OnReceiveError(int err_code, void * call_back_object)
{
	switch(err_code)
	{
	case PQMTE_RCV_INVALIDATE_DATA:
		cout << " error: receive invalidate data." << endl;
		break;
	case PQMTE_SERVER_VERSION_OLD:
		cout << " error: the multi-touch server is old for this client, please update the multi-touch server." << endl;
		break;
	case PQMTE_EXCEPTION_FROM_CALLBACKFUNCTION:
		cout << "**** some exceptions thrown from the call back functions." << endl;
		assert(0); //need to add try/catch in the callback functions to fix the bug;
		break;
	default:
		cout << " socket error, socket error code:" << err_code << endl;
	}
}

/*
 * Method Overview: Gets and prints the server resolution
 * Parameters (1): Server resolution
 * Parameters (2): Object that created the call back event
 * Return: None
 */
void TouchOverlayController:: OnGetServerResolution(int x, int y, void * call_back_object)
{
	cout << " server resolution:" << x << "," << y << endl;
}

/*
 * Method Overview: Gets and prints the device info
 * Parameters (1): Device info
 * Parameters (2): Object that created the call back event
 * Return: None
 */
void TouchOverlayController::OnGetDeviceInfo(const TouchDeviceInfo & deviceinfo,void *call_back_object)
{
	cout << " touch screen, SerialNumber: " << deviceinfo.serial_number <<",(" << deviceinfo.screen_width << "," << deviceinfo.screen_height << ")."<<  endl;
}

//Touch Gestures Handlers not being used at the moment
/*
//NOT USED
void TouchOverlayController:: OnTouchPoint(const TouchPoint & tp)
{
	switch(tp.point_event)
	{
	case TP_DOWN:
		cout << "  point " << tp.id << " come at (" << tp.x << "," << tp.y 
			<< ") width:" << tp.dx << " height:" << tp.dy << endl;
		break;
	case TP_MOVE:
		cout << "  point " << tp.id << " move at (" << tp.x << "," << tp.y 
			<< ") width:" << tp.dx << " height:" << tp.dy << endl;
		break;
	case TP_UP:
		cout << "  point " << tp.id << " leave at (" << tp.x << "," << tp.y 
			<< ") width:" << tp.dx << " height:" << tp.dy << endl;
		break;
	}
}

//NOT USED
void TouchOverlayController:: DefaultOnTG(const TouchGesture & tg,void * call_object)
{

}

/*
 * Method Overview: Handles the general move gesture events
 * Parameters: Received touch gesture
 * Return: None
 
void TouchOverlayController:: OnTG_Move(const TouchGesture & tg,void * call_object)
{
	//crear poligono de seleccion en lugar de cuadrado
	assert(tg.type == TG_MOVE && tg.param_size >= 2);
}

//NOT USED
void TouchOverlayController:: OnTG_Up(const TouchGesture & tg,void * call_object)
{
	assert(tg.type == TG_UP && tg.param_size >= 2);
}

//NOT USED
void TouchOverlayController:: OnTG_SecondDown(const TouchGesture & tg,void * call_object)
{
	assert(tg.type == TG_SECOND_DOWN && tg.param_size >= 4);
}

//NOT USED
void TouchOverlayController:: OnTG_SecondUp(const TouchGesture & tg,void * call_object)
{
	assert(tg.type == TG_SECOND_UP && tg.param_size >= 4);
}

//NOT USED
void TouchOverlayController::OnTG_SplitStart(const TouchGesture & tg,void * call_object)
{
	assert(tg.type == TG_SPLIT_START && tg.param_size >= 4);
	cout << "  the two fingers are splitting with one finger at: ( " 
		<< tg.params[0] << "," << tg.params[1] << " ),"
		<< " , the other at :( "
		<< tg.params[2] << "," << tg.params[3] << " )" << endl;
}

//NOT USED
void TouchOverlayController::OnTG_SplitEnd(const TouchGesture & tg,void * call_object)
{
	assert(tg.type == TG_SPLIT_END);
}
*/

/*
 * Method Overview: Handles the start touch gesture event
 * Parameters: Received touch gesture
 * Return: None
 */
void TouchOverlayController:: OnTG_TouchStart(const TouchGesture & tg,void * call_object)
{
	assert(tg.type == TG_TOUCH_START);

	//if not in draw mode, clears the selected touch region
	if(!(myCommander->getLinesDrawableFlag()))
	{
		roi_extremes.clear();
	}

	last_type = tg.type;
}

/*
 * Method Overview: Handles the received touch gesture events
 * Parameters: Received touch gesture
 * Return: None
 */
void TouchOverlayController:: OnTouchGesture(const TouchGesture & tg)
{
	if(TG_NO_ACTION == tg.type)
		return ;
	
	assert(tg.type <= TG_TOUCH_END);
	//DefaultOnTG(tg,this); //Enable if this handler is needed
	PFuncOnTouchGesture pf = m_pf_on_tges[tg.type];
	if(NULL != pf){
		pf(tg,this);
	}
}

/*
 * Method Overview: Handles the received touch_down events
 * Parameters: Received touch gesture
 * Return: None
 */
void TouchOverlayController:: OnTG_Down(const TouchGesture & tg,void * call_object)
{
	assert(tg.type == TG_DOWN && tg.param_size >= 2);
	
	if(myCommander->getLinesDrawableFlag())
	{
		OpenGLtouchControls(ADD_POINT,annotationCounter,(long double)tg.params[0],(long double)tg.params[1]);
	}

	last_type = tg.type;
} 

/*
 * Method Overview: Handles the received click events
 * Parameters: Received touch gesture
 * Return: None
 */
void TouchOverlayController:: OnTG_Click(const TouchGesture & tg,void * call_object)
{
	assert(tg.type == TG_CLICK);

	int button_clicked = myGUI->clickAnalysis(tg.params[0],tg.params[1]);

	if(!button_clicked)
	{
		if(!(myCommander->getVirtualAnnotationCreationFlag()))
		{
			//Checks if it is on editing mode
			if(!(myCommander->getLinesDrawableFlag()) && !(myCommander->getPointsDrawableFlag()))
			{
				int annotation_selected_id = myGUI->checkAnnotationSelected((long double)tg.params[0],(long double)tg.params[1]);

				if(annotation_selected_id==-1)
				{
					myCommander->setVirtualAnnotationSelectedFlag(0);

					myCommander->setRoiDrawnFlag(1);

					/*
					 * Initializes the extreme values as:
					 * [0] = MinX. Initizalized as a big value
					 * [1] = MinY. Initizalized as a big value
					 * [2] = MaxX. Initizalized as a small value
					 * [3] = MaxY. Initizalized as a small value
					 */
					roi_extremes.push_back(BIG_VALUE);
					roi_extremes.push_back(BIG_VALUE);
					roi_extremes.push_back(SMALL_VALUE);
					roi_extremes.push_back(SMALL_VALUE);
				}
			}
			//Checks if the annotations panel was clicked
			if (myCommander->getAnnotationPanelShownFlag() && (int)tg.params[0] < OPEN_PANEL_TAB_MIN_X 
				&& (int)tg.params[0] > CLOSED_PANEL_TAB_MAX_X)
			{
				selected_annotation_code = myGUI->touchedAnnotationIdentification(tg.params[0],tg.params[1]);

				myCommander->setVirtualAnnotationCreationFlag(1);

				myCommander->setLinesDrawableFlag(0);
				myCommander->setPointsDrawableFlag(0);
			}
			//Checks if it is on draw points mode
			else if(myCommander->getPointsDrawableFlag())
			{
				OpenGLtouchControls(CLEAR_LINE,NULL,NULL,NULL);

				OpenGLtouchControls(ADD_POINT_ANNOTATION,annotationCounter,(long double)tg.params[0],(long double)tg.params[1]);

				annotationCounter++;
			}
		}
		else
		{
			myGUI->createVirtualAnnotation(annotationCounter,(long double)tg.params[0],(long double)tg.params[1],selected_annotation_code);

			myCommander->setVirtualAnnotationCreationFlag(0);

			annotationCounter++;
		}
	}

	last_type = tg.type;
}

/*
 * Method Overview: Handles the received move_right events
 * Parameters: Received touch gesture
 * Return: None
 */
void TouchOverlayController:: OnTG_MoveRight(const TouchGesture & tg,void * call_object)
{
	assert(tg.type == TG_MOVE_RIGHT);
	if(myCommander->getLinesDrawableFlag())
	{
		myCommander->setLineDrawnFlag(1);
		OpenGLtouchControls(ADD_POINT,annotationCounter,(long double)tg.params[0],(long double)tg.params[1]);
	}
	else
	{
		myCommander->setRoiDrawnFlag(1);
		roi_extremes.push_back((long double)tg.params[0]);
		roi_extremes.push_back((long double)tg.params[1]);
	}

	last_type = tg.type;
}

/*
 * Method Overview: Handles the received move_left events
 * Parameters: Received touch gesture
 * Return: None
 */
void TouchOverlayController:: OnTG_MoveLeft(const TouchGesture & tg,void * call_object)
{
	assert(tg.type == TG_MOVE_LEFT);
	if(myCommander->getLinesDrawableFlag())
	{
		myCommander->setLineDrawnFlag(1);
		OpenGLtouchControls(ADD_POINT,annotationCounter,(long double)tg.params[0],(long double)tg.params[1]);
	}
	else
	{
		myCommander->setRoiDrawnFlag(1);
		roi_extremes.push_back((long double)tg.params[0]);
		roi_extremes.push_back((long double)tg.params[1]);
	}

	last_type = tg.type;
}

/*
 * Method Overview: Handles the received move_down events
 * Parameters: Received touch gesture
 * Return: None
 */
void TouchOverlayController:: OnTG_MoveDown(const TouchGesture & tg,void * call_object)
{
	assert(tg.type == TG_MOVE_DOWN);
	if(myCommander->getLinesDrawableFlag())
	{
		myCommander->setLineDrawnFlag(1);
		OpenGLtouchControls(ADD_POINT,annotationCounter,(long double)tg.params[0],(long double)tg.params[1]);
	}
	else
	{
		myCommander->setRoiDrawnFlag(1);
		roi_extremes.push_back((long double)tg.params[0]);
		roi_extremes.push_back((long double)tg.params[1]);
	}

	last_type = tg.type;
}

/*
 * Method Overview: Handles the received move_up events
 * Parameters: Received touch gesture
 * Return: None
 */
void TouchOverlayController:: OnTG_MoveUp(const TouchGesture & tg,void * call_object)
{
	assert(tg.type == TG_MOVE_UP);
	if(myCommander->getLinesDrawableFlag())
	{
		myCommander->setLineDrawnFlag(1);
		OpenGLtouchControls(ADD_POINT,annotationCounter,(long double)tg.params[0],(long double)tg.params[1]);
	}
	else
	{
		myCommander->setRoiDrawnFlag(1);
		roi_extremes.push_back((long double)tg.params[0]);
		roi_extremes.push_back((long double)tg.params[1]);
	}

	last_type = tg.type;
}

/*
 * Method Overview: Handles the received touch end events
 * Parameters: Received touch gesture
 * Return: None
 */
void TouchOverlayController:: OnTG_TouchEnd(const TouchGesture & tg,void * call_object)
{
	assert(tg.type == TG_TOUCH_END);
	
	if(last_type == TG_ROTATE_CLOCK || last_type == TG_ROTATE_ANTICLOCK || last_type == TG_SPLIT_APART || 
		last_type == TG_SPLIT_CLOSE || last_type == TG_NEAR_PARREL_MOVE_RIGHT || last_type == TG_NEAR_PARREL_MOVE_LEFT || 
		last_type == TG_NEAR_PARREL_MOVE_UP || last_type == TG_NEAR_PARREL_MOVE_DOWN)
	{
		if(myCommander->getVirtualAnnotationSelectedFlag())
		{
			myGUI->startJSONAnnotationUpdate();
		}
		else if(myCommander->getLineSelectedFlag())
		{
			startJSONLineUpdate();
		}
	}

	//is draw mode is on, check if there is any line to draw
	if(myCommander->getLinesDrawableFlag())
	{
		if(myCommander->getLineDrawnFlag())
		{
			OpenGLtouchControls(ADD_LINE,annotationCounter,NULL,NULL);
		
			myCommander->setLineDrawnFlag(0);

			annotationCounter++;
		}
		OpenGLtouchControls(CLEAR_LINE,NULL,NULL,NULL);
	}
	//is draw mode is off, check if there is a line selection roi
	else
	{
		if(myCommander->getRoiDrawnFlag())
		{
			roi_extremes.push_back(roi_extremes.at(0));
			roi_extremes.push_back(roi_extremes.at(1));

			myCommander->setLineSelectedFlag(pointInPolygon(roi_extremes));

			myCommander->setRoiDrawnFlag(0);
		}
	}

	last_type = tg.type;
}

/*
 * Method Overview: Handles the received rotate_clockwise events
 * Parameters: Received touch gesture
 * Return: None
 */
void TouchOverlayController::OnTG_RotateClock(const TouchGesture & tg,void * call_object)
{
	assert(tg.type == TG_ROTATE_CLOCK);
	
	if(myCommander->getVirtualAnnotationSelectedFlag())
	{
		myGUI->GUItouchControls(ROTATE_CLK);
	}
	else if(myCommander->getLineSelectedFlag())
	{
		OpenGLtouchControls(ROTATE_CLK,NULL,NULL,NULL);
	}

	last_type = tg.type;
}

/*
 * Method Overview: Handles the received rotate_anticlockwise event
 * Parameters: Received touch gesture
 * Return: None
 */
void TouchOverlayController::OnTG_RotateAntiClock(const TouchGesture & tg,void * call_object)
{
	assert(tg.type == TG_ROTATE_ANTICLOCK);
	
	if(myCommander->getVirtualAnnotationSelectedFlag())
	{
		myGUI->GUItouchControls(ROTATE_CNTR_CLK);
	}
	else if(myCommander->getLineSelectedFlag())
	{
		OpenGLtouchControls(ROTATE_CNTR_CLK,NULL,NULL,NULL);
	}

	last_type = tg.type;
}

/*
 * Method Overview: Handles the received split_apart events
 * Parameters: Received touch gesture
 * Return: None
 */
void TouchOverlayController::OnTG_SplitApart(const TouchGesture & tg,void * call_object)
{
	assert(tg.type == TG_SPLIT_APART && tg.param_size >= 1);
	
	if(myCommander->getVirtualAnnotationSelectedFlag())
	{
		myGUI->GUItouchControls(ZOOM_IN);
	}
	else if(myCommander->getLineSelectedFlag())
	{
		OpenGLtouchControls(ZOOM_IN,NULL,NULL,NULL);
	}

	last_type = tg.type;
}

/*
 * Method Overview: Handles the received split_close events
 * Parameters: Received touch gesture
 * Return: None
 */
void TouchOverlayController::OnTG_SplitClose(const TouchGesture & tg,void * call_object)
{
	assert(tg.type == TG_SPLIT_CLOSE && tg.param_size >= 1);
	
	if(myCommander->getVirtualAnnotationSelectedFlag())
	{
		myGUI->GUItouchControls(ZOOM_OUT);
	}
	else if(myCommander->getLineSelectedFlag())
	{
		OpenGLtouchControls(ZOOM_OUT,NULL,NULL,NULL);
	}

	last_type = tg.type;
}

/*
 * Method Overview: Handles the received parrell_move_right events
 * Parameters: Received touch gesture
 * Return: None
 */
void TouchOverlayController::onTG_NearParrellMoveRight(const TouchGesture & tg,void * call_object)
{
	assert(tg.type == TG_NEAR_PARREL_MOVE_RIGHT);
	
	if(myCommander->getVirtualAnnotationSelectedFlag())
	{
		myGUI->GUItouchControls(TRANSLATE_RIGHT);
	}
	else if(myCommander->getLineSelectedFlag())
	{
		OpenGLtouchControls(TRANSLATE_RIGHT,NULL,NULL,NULL);
	}

	last_type = tg.type;
}

/*
 * Method Overview: Handles the received parrell_move_left events
 * Parameters: Received touch gesture
 * Return: None
 */
void TouchOverlayController::onTG_NearParrellMoveLeft(const TouchGesture & tg,void * call_object)
{
	assert(tg.type == TG_NEAR_PARREL_MOVE_LEFT);
	
	if(myCommander->getVirtualAnnotationSelectedFlag())
	{
		myGUI->GUItouchControls(TRANSLATE_LEFT);
	}
	else if(myCommander->getLineSelectedFlag())
	{
		OpenGLtouchControls(TRANSLATE_LEFT,NULL,NULL,NULL);
	}

	last_type = tg.type;

}

/*
 * Method Overview: Handles the received parrell_move_up events
 * Parameters: Received touch gesture
 * Return: None
 */
void TouchOverlayController::onTG_NearParrellMoveUp(const TouchGesture & tg,void * call_object)
{
	assert(tg.type == TG_NEAR_PARREL_MOVE_UP);

	if(myCommander->getVirtualAnnotationSelectedFlag())
	{
		myGUI->GUItouchControls(TRANSLATE_UP);
	}
	else if(myCommander->getLineSelectedFlag())
	{
		OpenGLtouchControls(TRANSLATE_UP,NULL,NULL,NULL);
	}

	last_type = tg.type;
}

/*
 * Method Overview: Handles the received parrell_move_down events
 * Parameters: Received touch gesture
 * Return: None
 */
void TouchOverlayController::onTG_NearParrellMoveDown(const TouchGesture & tg,void * call_object)
{
	assert(tg.type == TG_NEAR_PARREL_MOVE_DOWN);
	
	if(myCommander->getVirtualAnnotationSelectedFlag())
	{
		myGUI->GUItouchControls(TRANSLATE_DOWN);
	}
	else if(myCommander->getLineSelectedFlag())
	{
		OpenGLtouchControls(TRANSLATE_DOWN,NULL,NULL,NULL);
	}

	last_type = tg.type;
}
