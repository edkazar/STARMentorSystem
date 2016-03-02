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
 * Name: VideoManager.cpp
 *
 * Overview: .cpp of VideoManager.h
 */
///////////////////////////////////////////////////////////////////

//Include its header file
#include "VideoManager.h"

/*
 * Method Overview: Constructor of the class
 * Parameters (1): Instance of the Communication Manager server
 * Parameters (2): Instance of the Command Center
 * Return: Instance of the class
 */
VideoManager::VideoManager(CommunicationManager* server, CommandCenter* pCommander, GUIManager* pGUI) 
{
	//Sets the given instance as the one that will be used
	myServer = server;

	//Image constants
	rescamX = 640;
	//rescamY = 400; //Tablet resolution
	rescamY = 480; //Webcam resolution

	//Screen constants
	rescompX = 1920;
	rescompY = 1080;

	//determined by the resolution of the camera
	aspectRatioX = 16;
	aspectRatioY = 9;

	//determined by the user
	panStep = 10;
	zoomScale = 2;
	rotationDegree = 0.0;

	//Create the region of interest
	tl = Point(0,0);
	br = Point(rescamX,rescamY);
	roi= Rect(tl,br);

	//Inits the GUI Manager
	GUIcreator = pGUI;
}

/*
 * Method Overview: Calls the methods to obtain and create an image
 * Parameters: None
 * Return: None
 */
void VideoManager::initWindow()
{
	//The size of the window to create
	Size size = Size(rescompX,rescompY);

	//Image matrices that will be used to create the final image
	Mat temp, rotated, flipped, show;

	//Creates a matrix of zeros. 
	//The size of it will be the size of the obtained webcam image
	Mat img = Mat::zeros(rescamX,rescamY,CV_8UC3);
	//Calculates the total size of image matriz recently created
	int imgSize = (int)(img.total()*img.elemSize());
	//Buffer to store the receieve data stream in
	char* sockData;
	//Allocates enough memory for the buffer.
	sockData = (char *)malloc(sizeof(char)*imgSize+1);

	//Infinite loop to obtain and create an image to be displayed
	while(1)
	{	
		//Remove the /**/ when using video streaming
		//Comment with /**/ when using an image as the background
		//Add or remove the /**/ right before and after the ///////
		///////////////////////////////////////////////////////////
		
		//Receives the image data stream from the client
		int data_length = myServer->receiveFromClients(sockData, imgSize, VIDEO_NETWORK_CODE);

		if (data_length <= 0) 
        {
			//nodata or incomplete data
            continue;
        }

		//Creates an image from the just obtained data stream
		Mat img(Size(rescamX, rescamY), CV_8UC3, sockData);
		
		///////////////////////////////////////////////////////////

		/*
		 * Comment when using video streaming
		 * Uncomment when using an image as the background
		 */
		//img = imread("../images/surgical_room.jpg");
		
		//Flips the image around both axis (to fit OpenGL window)
		flip(img,flipped,0);
		
		//Rotation starts here
		//Finds the center of the region of interest
		Point2f pc(((br.x-tl.x)/2.0f)+tl.x, ((br.y-tl.y)/2.0f)+tl.y);

		//Creates a rotation matrix around the center of the roi
		temp = getRotationMatrix2D(pc, rotationDegree, 1.0);

		//Applies the rotation matrix to every pixel on the image
		warpAffine(flipped, rotated, temp, flipped.size());
		//Rotation ends here
		
		//Resizes the image
		resize(rotated(roi),show,size);

		//Enables the image to be controlled by keyboard events
		keyboardInteractions();

		if(!show.empty())
		{	
			//OpenGL Call
			setOpenCVImage(GUIcreator->createGUI(show));
		}
	}
}

/*
 * Method Overview: Applies geometrical trans based on touch events
 * Parameters: Generated event and its (x,y) coordinates on screen
 * Return: None
 */
void VideoManager::OpenCVtouchControls(int command, long double x, long double y)
{
	switch (command)
    {		
		//Rotations
		case ROTATE_CNTR_CLK://rotate counterclockwise
		{
			//Change the degree by which the image is being rotated
			rotationDegree -= 2;
		}
		break;

		case ROTATE_CLK://rotate clockwise
		{
			//Change the degree by which the image is being rotated
			rotationDegree += 2;
		}
		break;

		//Zooms
		case ZOOM_IN://zoom in
		{
			//Evaluates if the image can zoomed in
			if (tl.x+(aspectRatioX*zoomScale)<((br.x-tl.x)/2.0f)+tl.x)
			{
				//Modifies the region of interest
				tl = Point(tl.x+(aspectRatioX*zoomScale),tl.y+(aspectRatioY*zoomScale));
				br = Point(br.x-(aspectRatioX*zoomScale),br.y-(aspectRatioY*zoomScale));
				roi= Rect(tl,br);
			}
		}
		break;

		case ZOOM_OUT://zoom out
		{
			//Evaluates if the image can zoomed out
			if (br.x+(aspectRatioX*zoomScale)<=rescamX && br.y+(aspectRatioY*zoomScale)<=rescamY
				&& tl.x-(aspectRatioX*zoomScale)>=0 && tl.y-(aspectRatioY*zoomScale)>=0)
			{
				//Modifies the region of interest
				tl = Point(tl.x-(aspectRatioX*zoomScale),tl.y-(aspectRatioY*zoomScale));
				br = Point(br.x+(aspectRatioX*zoomScale),br.y+(aspectRatioY*zoomScale));
				roi= Rect(tl,br); 
			}
		}
		break;
	
		/*
		 * PANS AND ZOOMS ARE "UNITED"
		 * e.g if you want to zoom out, you need to set into a 
		 * "zoom out-able" position in the image
		 */

		//Pans
		case TRANSLATE_UP://up
		{
			//Evaluates if the can be translated up
			if (tl.y-panStep>0)
			{
				//Modifies the region of interest
				tl = Point(tl.x,tl.y-panStep);
				br = Point(br.x,br.y-panStep);
				roi= Rect(tl,br); 
			}
		}
		break;

		case TRANSLATE_DOWN://down
		{
			//Evaluates if the can be translated down
			if (br.y+panStep<rescamY)
			{
				//Modifies the region of interest
				tl = Point(tl.x,tl.y+panStep);
				br = Point(br.x,br.y+panStep);
				roi= Rect(tl,br); 
			}
		}
		break;

		case TRANSLATE_RIGHT://right
		{
			//Evaluates if the can be translated right
			if (tl.x-panStep>0)
			{
				//Modifies the region of interest
				tl = Point(tl.x-panStep,tl.y);
				br = Point(br.x-panStep,br.y);
				roi= Rect(tl,br); 
			}
		}
		break;

		case TRANSLATE_LEFT://left
		{
			//Evaluates if the can be translated left
			if (br.x+panStep<rescamX)
			{
				//Modifies the region of interest
				tl = Point(tl.x+panStep,tl.y);
				br = Point(br.x+panStep,br.y);
				roi= Rect(tl,br); 
			}
		}
		break;
	}
}

/*
 * Method Overview: Applies transformation based on keyboard events
 * Parameters: None
 * Return: None
 */
void VideoManager::keyboardInteractions()
{
	//Wait for a keyboard event to happen
	key = waitKey(40);

	//Zooms
	if ( key=='i' )//Zoom in
	{
		//Evaluates if the image can zoomed in
		if (tl.x+(aspectRatioX*zoomScale)<((br.x-tl.x)/2.0f)+tl.x)
		{
			//Modifies the region of interest
			tl = Point(tl.x+(aspectRatioX*zoomScale),tl.y+(aspectRatioY*zoomScale));
			br = Point(br.x-(aspectRatioX*zoomScale),br.y-(aspectRatioY*zoomScale));
			roi= Rect(tl,br);
		}
	}

	if ( key=='o' )//Zoom out
	{
		//Evaluates if the image can zoomed out
		if (br.x+(aspectRatioX*zoomScale)<=rescamX && br.y+(aspectRatioY*zoomScale)<=rescamY
			&& tl.x-(aspectRatioX*zoomScale)>=0 && tl.y-(aspectRatioY*zoomScale)>=0)//ojo?
		{
			//Modifies the region of interest
			tl = Point(tl.x-(aspectRatioX*zoomScale),tl.y-(aspectRatioY*zoomScale));
			br = Point(br.x+(aspectRatioX*zoomScale),br.y+(aspectRatioY*zoomScale));
			roi= Rect(tl,br); 
		}
	}

	//Rotations
	if ( key=='z' )//Rotate clockwise
	{
		//Change the degree by which the image is being rotated
		rotationDegree += 2;
	}

	if ( key=='x' )//Rotate counter-clockwise
	{
		//Change the degree by which the image is being rotated
		rotationDegree -= 2;
	}

	/*
	 * PANS AND ZOOMS ARE "UNITED"
	 * e.g if you want to zoom out, you need to set into a 
	 * "zoom out-able" position in the image
	 */

	//Pans
	if ( key=='w' )//up
	{
		//Evaluates if the can be translated up
		if (tl.y-panStep>0)
		{
			tl = Point(tl.x,tl.y-panStep);
			br = Point(br.x,br.y-panStep);
			roi= Rect(tl,br); 
		}
	}

	if ( key=='s' )//down
	{
		//Evaluates if the can be translated down
		if (br.y+panStep<rescamY)
		{
			//Modifies the region of interest
			tl = Point(tl.x,tl.y+panStep);
			br = Point(br.x,br.y+panStep);
			roi= Rect(tl,br); 
		}
	}

	if ( key=='d' )//left
	{
		//Evaluates if the can be translated left
		if (tl.x-panStep>0)
		{
			//Modifies the region of interest
			tl = Point(tl.x-panStep,tl.y);
			br = Point(br.x-panStep,br.y);
			roi= Rect(tl,br); 
		}
	}

	if ( key=='a' )//right
	{
		//Evaluates if the can be translated right
		if (br.x+panStep<rescamX)
		{
			//Modifies the region of interest
			tl = Point(tl.x+panStep,tl.y);
			br = Point(br.x+panStep,br.y);
			roi= Rect(tl,br); 
		}
	}

	if ( key=='a' )//right
	{
		if (br.x+panStep<rescamX)
		{
			//Modifies the region of interest
			tl = Point(tl.x+panStep,tl.y);
			br = Point(br.x+panStep,br.y);
			roi= Rect(tl,br); 
		}
	}

	if ( key=='r' ) //Reverts to original
	{
		//Resets region of interest and rotation degree
		rotationDegree = 0.0;
		tl = Point(0,0);
		br = Point(rescamX,rescamY);
		roi= Rect(tl,br); 
	}
}