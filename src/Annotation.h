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
 * Name: Annotation.h
 *
 * Overview: This class contains the general variables and methods
 * needed to represent a annotation. Important detail as its ID,
 * position and anchoring related information are stored in here.
 * This class is a parent for the other types of annotations.
 */
///////////////////////////////////////////////////////////////////

//Define guard
#ifndef ANNOTATION_H
#define ANNOTATION_H

using namespace std;//Standard Library

class Annotation
{
public:
	//-------------------------Methods---------------------------//
	//Return Id of the annotation
	int getID();

	//Return the selected state of the annotation
	int getSelectedState();

	//Return the extreme values of the annotation
	long double* getExtremePoints();

	//Changes the selected state of the annotation
	void setSelectedState(int state);

	//recalculates the center of the annotation after a geom transf
	void recalculateCenter();

	//returs the center of the annotation
	long double* getAnnotationCenter();

	//------------------------Variables--------------------------//
	//None

protected:
	//------------------------Variables--------------------------//
	//Id of this annotation
	int myID;

	//whereas or not the annotation is currently selected
	int selected_state;

	//annotation center
	long double annotation_center[2];

	//annotation min-max values
	long double annotation_extremes[4];
};
#endif