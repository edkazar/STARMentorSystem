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
 * Name: LineAnnotation.cpp
 *
 * Overview: .cpp of VirtualAnnotation.h
 */
///////////////////////////////////////////////////////////////////

//Include its header file
#include "VirtualAnnotation.h"

/*
 * Method Overview: Constructor of the class
 * Parameters: Id of the annotation
 * Return: Instance of the class
 */
VirtualAnnotation::VirtualAnnotation(int Id, long double posX, long double posY, int code)
{
	myID = Id;

	selected_state = 1;

	myCode = code;

	findImages(code);
	findAnchorPoints(code);

	myZoom = 0.09f;
	myRotation = 0.0f;

	annotation_center[0] = posX;
	annotation_center[1] = posY;
	
	annotation_extremes[0] = posX-((selectedImage.cols/2)*myZoom);
	annotation_extremes[1] = posY-((selectedImage.rows/2)*myZoom);
	annotation_extremes[2] = posX+((selectedImage.cols/2)*myZoom);
	annotation_extremes[3] = posY+((selectedImage.rows/2)*myZoom);

}

/*
 * Method Overview: Gets the code of the virtual annotation
 * Parameters: None
 * Return: Virtual annotation code
 */
int VirtualAnnotation::getCode()
{
	return myCode;
}

/*
 * Method Overview: Gets the zoom value of the virtual annotation
 * Parameters: None
 * Return: Virtual annotation zoom value
 */
long double VirtualAnnotation::getZoomValue()
{
	return myZoom;
}

/*
 * Method Overview: Gets the virtual annotation's rotation value 
 * Parameters: None
 * Return: Virtual annotation rotation value
 */
long double VirtualAnnotation::getRotationValue()
{
	return myRotation;
}

/*
 * Method Overview: Gets the path to the image that should be shown
 * Parameters: None
 * Return: Path to the image to be loaded
 */
cv::Mat VirtualAnnotation::getImage()
{
	//Resizes the image
	cv::Mat resized;

	int sizeX = (int)(1920*myZoom);
	int sizeY;

	if(selected_state)
	{
		sizeY = (int)(((selectedImage.rows*1920)/selectedImage.cols)*myZoom);
		cv::resize(selectedImage,resized,cv::Size(sizeX,sizeY));
	}
	else
	{
		sizeY = (int)(((deselectedImage.rows*1920)/deselectedImage.cols)*myZoom);
		cv::resize(deselectedImage,resized,cv::Size(sizeX,sizeY));
	}

	return resized;
}

/*
 * Method Overview: Finds whether or not a pixel is transparent
 * Parameters: (X,Y) coordinate in the image of the clicked pixel
 * Return: Whether or not the pixel is transparent
 */
int VirtualAnnotation::checkPixelTransparency(long double posX, long double posY)
{
	//gets the actual image
	cv::Mat transformed = imageRotation(getImage());

	long double X_diff_in_background = posX - annotation_center[0];
	long double Y_diff_in_background = posY - annotation_center[1];

	long double posXinImage = transformed.cols/2 + X_diff_in_background;
	long double posYinImage = transformed.rows/2 + Y_diff_in_background;
	
	double opacity =((double)transformed.data[(transformed.rows-(int)posYinImage) * transformed.step 
		+ (int)posXinImage * transformed.channels() + 3])/ 255.;

	return (int)opacity;
}

/*
 * Method Overview: Changes the zoom amount by a specific value
 * Parameters: Value to multiply the zoom one for
 * Return: None
 */
void VirtualAnnotation::modifyZoomValue(long double zoom)
{
	myZoom *= zoom;
}

/*
 * Method Overview: Changes the rotation amount by a specific value
 * Parameters: Value to multiply the rotation one for
 * Return: None
 */
void VirtualAnnotation::modifyRotationValue(long double angle)
{
	myRotation += angle;	
}

/*
 * Method Overview: Rotates an image around its anchor point
 * Parameters: Image to rotate
 * Return: Rotated image
 */
cv::Mat VirtualAnnotation::imageRotation(cv::Mat to_rotate)
{
	long double anchoring[2];
	
	getAnchorPoints(anchoring);

	cv::Mat rotated, matrix;

	//Make a larger image
    int rows = to_rotate.rows*3;
    int cols = to_rotate.cols*3;
    int largest = 0;

    if ( rows > cols )
	{
        largest = rows;
    }
	else
	{
        largest = cols;
    }
    cv::Mat temp = cv::Mat::zeros(largest, largest, CV_8UC4);

    cv::Rect roi;

	int rectInitialX, rectInitialY;

	rectInitialX = temp.cols/2 - (to_rotate.cols/2 - (int)anchoring[0]);
	rectInitialY = temp.rows/2 - (to_rotate.rows/2 - (int)anchoring[1]);

	roi = cv::Rect((int)rectInitialX, (int)rectInitialY, to_rotate.cols, to_rotate.rows);

	// Copy the original to the black large temp image
	to_rotate.copyTo(temp(roi));
	rotated = temp.clone();

	//Apply the rotation
	cv::Point2f pt((float)temp.cols/2, (float)temp.rows/2);
	matrix = getRotationMatrix2D(pt, myRotation, 1.0);
	warpAffine(temp, rotated, matrix, cv::Size(temp.cols, temp.rows));

	//Recalculates the image important points
	annotation_extremes[0] = annotation_center[0]-(rotated.cols/2);
	annotation_extremes[1] = annotation_center[1]-(rotated.rows/2);
	annotation_extremes[2] = annotation_center[0]+(rotated.cols/2);
	annotation_extremes[3] = annotation_center[1]+(rotated.rows/2);

	recalculateCenter();

	return rotated;
}

/*
 * Method Overview: Searchs for the respective image paths
 * Parameters: Code of the annotation
 * Return: None
 */
void VirtualAnnotation::findImages(int code)
{
	//depending on the code, finds the respective images to shown
	switch(code)
	{
		case BVM_CODE:
			selectedImage = cv::imread(BVM_SELECTED_IMAGE_PATH,-1);
			deselectedImage = cv::imread(BVM_SHADOW_IMAGE_PATH,-1);
			break;

		case ETTUBE_CODE:
			selectedImage = cv::imread(ETTUBE_SELECTED_IMAGE_PATH,-1);
			deselectedImage = cv::imread(ETTUBE_SHADOW_IMAGE_PATH,-1);
			break;

		case HEMOSTAT_CODE:
			selectedImage = cv::imread(HEMOSTAT_SELECTED_IMAGE_PATH,-1);
			deselectedImage = cv::imread(HEMOSTAT_SHADOW_IMAGE_PATH,-1);
			break;

		case IODINE_SWAB_CODE:
			selectedImage = cv::imread(IODINE_SWAB_SELECTED_IMAGE_PATH,-1);
			deselectedImage = cv::imread(IODINE_SWAB_SHADOW_IMAGE_PATH,-1);
			break;

		case LONGHOOK_CODE:
			selectedImage = cv::imread(LONGHOOK_SELECTED_IMAGE_PATH,-1);
			deselectedImage = cv::imread(LONGHOOK_SHADOW_IMAGE_PATH,-1);
			break;

		case RETRACTOR_CODE:
			selectedImage = cv::imread(RETRACTOR_SELECTED_IMAGE_PATH,-1);
			deselectedImage = cv::imread(RETRACTOR_SHADOW_IMAGE_PATH,-1);
			break;

		case SCALPEL_CODE:
			selectedImage = cv::imread(SCALPEL_SELECTED_IMAGE_PATH,-1);
			deselectedImage = cv::imread(SCALPEL_SHADOW_IMAGE_PATH,-1);
			break;

		case SCISSORS_CODE:
			selectedImage = cv::imread(SCISSORS_SELECTED_IMAGE_PATH,-1);
			deselectedImage = cv::imread(SCISSORS_SHADOW_IMAGE_PATH,-1);
			break;

		case STETHOSCOPE_CODE:
			selectedImage = cv::imread(STETHOSCOPE_SELECTED_IMAGE_PATH,-1);
			deselectedImage = cv::imread(STETHOSCOPE_SHADOW_IMAGE_PATH,-1);
			break;

		case SURGICAL_TAPE_CODE:
			selectedImage = cv::imread(SURGICAL_TAPE_SELECTED_IMAGE_PATH,-1);
			deselectedImage = cv::imread(SURGICAL_TAPE_SHADOW_IMAGE_PATH,-1);
			break;

		case SYRINGE_CODE:
			selectedImage = cv::imread(SYRINGE_SELECTED_IMAGE_PATH,-1);
			deselectedImage = cv::imread(SYRINGE_SHADOW_IMAGE_PATH,-1);
			break;

		case TWEEZERS_CODE:
			selectedImage = cv::imread(TWEEZERS_SELECTED_IMAGE_PATH,-1);
			deselectedImage = cv::imread(TWEEZERS_SHADOW_IMAGE_PATH,-1);
			break;

		case HAND_POINT_CODE:
			selectedImage = cv::imread(HAND_POINT_SELECTED_IMAGE_PATH,-1);
			deselectedImage = cv::imread(HAND_POINT_SHADOW_IMAGE_PATH,-1);
			break;

		case HAND_STRETCH_CODE:
			selectedImage = cv::imread(HAND_STRETCH_SELECTED_IMAGE_PATH,-1);
			deselectedImage = cv::imread(HAND_STRETCH_SHADOW_IMAGE_PATH,-1);
			break;

		case HAND_PALPATE_CODE:
			selectedImage = cv::imread(HAND_PALPATE_SELECTED_IMAGE_PATH,-1);
			deselectedImage = cv::imread(HAND_PALPATE_SHADOW_IMAGE_PATH,-1);
			break;

		case TEXT_CLOSE_CODE:
			selectedImage = cv::imread(TEXT_CLOSE_SELECTED_IMAGE_PATH,-1);
			deselectedImage = cv::imread(TEXT_CLOSE_SHADOW_IMAGE_PATH,-1);
			break;

		case TEXT_INCISION_CODE:
			selectedImage = cv::imread(TEXT_INCISION_SELECTED_IMAGE_PATH,-1);
			deselectedImage = cv::imread(TEXT_INCISION_SHADOW_IMAGE_PATH,-1);
			break;

		case TEXT_PALPATION_CODE:
			selectedImage = cv::imread(TEXT_PALPATION_SELECTED_IMAGE_PATH,-1);
			deselectedImage = cv::imread(TEXT_PALPATION_SHADOW_IMAGE_PATH,-1);
			break;

		case TEXT_REMOVE_CODE:
			selectedImage = cv::imread(TEXT_REMOVE_SELECTED_IMAGE_PATH,-1);
			deselectedImage = cv::imread(TEXT_REMOVE_SHADOW_IMAGE_PATH,-1);
			break;

		case TEXT_STITCH_CODE:
			selectedImage = cv::imread(TEXT_STITCH_SELECTED_IMAGE_PATH,-1);
			deselectedImage = cv::imread(TEXT_STITCH_SHADOW_IMAGE_PATH,-1);
			break;
	}

	int timer;
	for(timer=0;timer<500;timer++)
	{

	}
}

/*
 * Method Overview: Searchs for the respective anchoring points
 * Parameters: Code of the annotation
 * Return: None
 */
void VirtualAnnotation::findAnchorPoints(int code)
{
	//depending on the code, finds the respective images to shown
	switch(code)
	{
		case BVM_CODE:
			myAnchorPoints[0] = (selectedImage.cols/2)-BVM_X_ANCHOR;
			myAnchorPoints[1] = (selectedImage.rows/2)-BVM_Y_ANCHOR;
			break;

		case ETTUBE_CODE:
			myAnchorPoints[0] = (selectedImage.cols/2)-ETTUBE_X_ANCHOR;
			myAnchorPoints[1] = (selectedImage.rows/2)-ETTUBE_Y_ANCHOR;
			break;

		case HEMOSTAT_CODE:
			myAnchorPoints[0] = (selectedImage.cols/2)-HEMOSTAT_X_ANCHOR;
			myAnchorPoints[1] = (selectedImage.rows/2)-HEMOSTAT_Y_ANCHOR;
			break;

		case IODINE_SWAB_CODE:
			myAnchorPoints[0] = (selectedImage.cols/2)-IODINE_SWAB_X_ANCHOR;
			myAnchorPoints[1] = (selectedImage.rows/2)-IODINE_SWAB_Y_ANCHOR;
			break;

		case LONGHOOK_CODE:
			myAnchorPoints[0] = (selectedImage.cols/2)-LONGHOOK_X_ANCHOR;
			myAnchorPoints[1] = (selectedImage.rows/2)-LONGHOOK_Y_ANCHOR;
			break;

		case RETRACTOR_CODE:
			myAnchorPoints[0] = (selectedImage.cols/2)-RETRACTOR_X_ANCHOR;
			myAnchorPoints[1] = (selectedImage.rows/2)-RETRACTOR_Y_ANCHOR;
			break;

		case SCALPEL_CODE:
			myAnchorPoints[0] = (selectedImage.cols/2)-SCALPEL_X_ANCHOR;
			myAnchorPoints[1] = (selectedImage.rows/2)-SCALPEL_Y_ANCHOR;
			break;

		case SCISSORS_CODE:
			myAnchorPoints[0] = (selectedImage.cols/2)-SCISSORS_X_ANCHOR;
			myAnchorPoints[1] = (selectedImage.rows/2)-SCISSORS_Y_ANCHOR;
			break;

		case STETHOSCOPE_CODE:
			myAnchorPoints[0] = (selectedImage.cols/2)-STETHOSCOPE_X_ANCHOR;
			myAnchorPoints[1] = (selectedImage.rows/2)-STETHOSCOPE_Y_ANCHOR;
			break;

		case SURGICAL_TAPE_CODE:
			myAnchorPoints[0] = (selectedImage.cols/2)-SURGICAL_TAPE_X_ANCHOR;
			myAnchorPoints[1] = (selectedImage.rows/2)-SURGICAL_TAPE_Y_ANCHOR;
			break;

		case SYRINGE_CODE:
			myAnchorPoints[0] = (selectedImage.cols/2)-SYRINGE_X_ANCHOR;
			myAnchorPoints[1] = (selectedImage.rows/2)-SYRINGE_Y_ANCHOR;
			break;

		case TWEEZERS_CODE:
			myAnchorPoints[0] = (selectedImage.cols/2)-TWEEZERS_X_ANCHOR;
			myAnchorPoints[1] = (selectedImage.rows/2)-TWEEZERS_Y_ANCHOR;
			break;

		case HAND_POINT_CODE:
			myAnchorPoints[0] = (selectedImage.cols/2)-HAND_POINT_X_ANCHOR;
			myAnchorPoints[1] = (selectedImage.rows/2)-HAND_POINT_Y_ANCHOR;
			break;

		case HAND_STRETCH_CODE:
			myAnchorPoints[0] = (selectedImage.cols/2)-HAND_STRETCH_X_ANCHOR;
			myAnchorPoints[1] = (selectedImage.rows/2)-HAND_STRETCH_Y_ANCHOR;
			break;

		case HAND_PALPATE_CODE:
			myAnchorPoints[0] = (selectedImage.cols/2)-HAND_PALPATE_X_ANCHOR;
			myAnchorPoints[1] = (selectedImage.rows/2)-HAND_PALPATE_Y_ANCHOR;
			break;

		case TEXT_CLOSE_CODE:
			myAnchorPoints[0] = (selectedImage.cols/2)-TEXT_CLOSE_X_ANCHOR;
			myAnchorPoints[1] = (selectedImage.rows/2)-TEXT_CLOSE_Y_ANCHOR;
			break;

		case TEXT_INCISION_CODE:
			myAnchorPoints[0] = (selectedImage.cols/2)-TEXT_INCISION_X_ANCHOR;
			myAnchorPoints[1] = (selectedImage.rows/2)-TEXT_INCISION_Y_ANCHOR;
			break;

		case TEXT_PALPATION_CODE:
			myAnchorPoints[0] = (selectedImage.cols/2)-TEXT_PALPATION_X_ANCHOR;
			myAnchorPoints[1] = (selectedImage.rows/2)-TEXT_PALPATION_Y_ANCHOR;
			break;

		case TEXT_REMOVE_CODE:
			myAnchorPoints[0] = (selectedImage.cols/2)-TEXT_REMOVE_X_ANCHOR;
			myAnchorPoints[1] = (selectedImage.rows/2)-TEXT_REMOVE_Y_ANCHOR;
			break;

		case TEXT_STITCH_CODE:
			myAnchorPoints[0] = (selectedImage.cols/2)-TEXT_STITCH_X_ANCHOR;
			myAnchorPoints[1] = (selectedImage.rows/2)-TEXT_STITCH_Y_ANCHOR;
			break;
	}


	//annotation_center[0] = posX-((selectedImage.cols/2)*myZoom)+(myAnchorPoints[0]*myZoom);
	//annotation_center[1] = posY+((selectedImage.rows/2)*myZoom)-(myAnchorPoints[1]*myZoom);
}

/*
 * Method Overview: Gets the virtual annotation's anchor points 
 * Parameters: Array to store the anchor points value
 * Return: None
 */
void VirtualAnnotation::getAnchorPoints(long double* anchoring)
{
	long double sizeX = 1920*myZoom;
	long double sizeY = ((selectedImage.rows*1920)/selectedImage.cols)*myZoom;

	anchoring[0] = (myAnchorPoints[0]*(sizeX))/selectedImage.cols;
	anchoring[1] = (myAnchorPoints[1]*(sizeY))/selectedImage.rows;

}