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
 * Name: LineAnnotation.h
 *
 * Overview: This class contains all the variables needed to 
 * represent a line. Important details as related just to the line
 * type annotations are stored in this class.
 */
///////////////////////////////////////////////////////////////////

//Define guard
#ifndef LINEANNOTATION_H
#define LINEANNOTATION_H

//---------------------------Includes----------------------------//
#include <vector>//Enable the usage of the vector class
#include "Annotation.h"//General annotation values and methods

class LineAnnotation: public Annotation
{
public:
	//-------------------------Methods---------------------------//
	LineAnnotation(int Id);//Class Constructor

	//Initialices or clears the initial min-max line values
	void setInitialExtremes();

	//Add a point to the line
	void addPoint(long double x, long double y);

	//Return the points of the line
	vector<long double>* getPoints();
	
	//------------------------Variables--------------------------//
	//None

private:
	//-------------------------Methods---------------------------//
	//None

	//------------------------Variables--------------------------//
	//Points of the line annotation
	vector<long double> myPoints;

	//add own geom transf values
};

#endif