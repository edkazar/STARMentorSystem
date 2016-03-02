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
 * Name: VirtualAnnotation.h
 *
 * Overview: This class contains all the variables needed to 
 * represent a virtual annotation, which could be texts, hands or
 * tools. Important details as related just to the virtual type
 * annotations are stored in this class.
 */
///////////////////////////////////////////////////////////////////

//Define guard
#ifndef VIRTUALANNOTATION_H
#define VIRTUALANNOTATION_H

//---------------------------Includes----------------------------//
#include <opencv2/opencv.hpp>//OpenCV Core Library
#include "Annotation.h"//General annotation values and methods
#include "virtualAnnotationDefinitions.h"//Virtual annotation codes

class VirtualAnnotation: public Annotation
{
public:
	//-------------------------Methods---------------------------//
	VirtualAnnotation(int Id, long double posX, long double posY, int code);//Class Constructor

	//Returns the annotation code
	int getCode();

	//Returns the zoom value
	long double getZoomValue();

	//Returns the rotation value
	long double getRotationValue();

	//Returns the address to the .png of this annotation
	cv::Mat getImage();

	//Checks if a selected pixel in the image is transparent
	int checkPixelTransparency(long double posX, long double posY);

	//Modify the current zoom value
	void modifyZoomValue(long double zoom);

	//Modify the current rotation value
	void modifyRotationValue(long double angle);

	//Rotates an image around its center
	cv::Mat imageRotation(cv::Mat);

	//------------------------Variables--------------------------//
	//None

private:
	//-------------------------Methods---------------------------//
	//Searchs and assings the image paths of this annotation
	void findImages(int code);

	//Searchs and assings the anchoring points of this annotation
	void findAnchorPoints(int code);

	//Sets the image anchor points to an input array
	void getAnchorPoints(long double* anchoring);

	//------------------------Variables--------------------------//
	//selected image
	cv::Mat selectedImage;

	//deselected image
	cv::Mat deselectedImage;

	//annotation code
	int myCode;

	//Anchor points of the annotation 
	long double myAnchorPoints[2];

	//general zoom value
	long double myZoom;

	//general rotation value
	long double myRotation;
};

#endif