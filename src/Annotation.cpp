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
 * Name: Annotation.cpp
 *
 * Overview: .cpp of Annotation.h
 */
///////////////////////////////////////////////////////////////////

//Include its header file
#include "Annotation.h"

/*
 * Method Overview: Gets the Id of this specific annotation
 * Parameters: None
 * Return: Id of the annotation
 */
int Annotation::getID()
{
	return myID;
}

/*
 * Method Overview: Gets the selected state of this annotation
 * Parameters: None
 * Return: Selected state of the annotation
 */
int Annotation::getSelectedState()
{
	return selected_state;
}

/*
 * Method Overview: Return the extreme points of the annotation
 * Parameters: None
 * Return: Vector that contains the extreme points of a annotation
 */
long double* Annotation::getExtremePoints()
{
	return annotation_extremes;
}

/*
 * Method Overview: Changes the selected state of this annotation
 * Parameters: New selected state of the annotation
 * Return: None
 */
void Annotation::setSelectedState(int state)
{
	selected_state = state;
}

/*
 * Method Overview: Return the center of the annotation
 * Parameters: None
 * Return: Vector that contains the center of the annotation
 */
long double* Annotation::getAnnotationCenter()
{
	return annotation_center;
}

/*
 * Method Overview: Finds the center of the annotation
 * Parameters: None
 * Return: None
 */
void Annotation::recalculateCenter()
{
	//(Xmax + Xmin)/2
	annotation_center[0] = (annotation_extremes[2]+annotation_extremes[0])/2;

	//(Ymax + Ymin)/2
	annotation_center[1] = (annotation_extremes[3]+annotation_extremes[1])/2;
}