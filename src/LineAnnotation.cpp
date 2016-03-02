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
 * Overview: .cpp of LineAnnotation.h
 */
///////////////////////////////////////////////////////////////////

//Include its header file
#include "LineAnnotation.h"

//--------------------------Definitions--------------------------//
#define BIG_VALUE 10000
#define SMALL_VALUE -10000

/*
 * Method Overview: Constructor of the class
 * Parameters: Id of the line
 * Return: Instance of the class
 */
LineAnnotation::LineAnnotation(int Id)
{
	myID = Id;

	selected_state = 0;

	setInitialExtremes();
}

/*
 * Method Overview: Cleans the extreme values of the line
 * Parameters: None
 * Return: None
 */
void LineAnnotation::setInitialExtremes()
{
	/*
	 * Initializes the extreme values as:
	 * [0] = MinX. Initizalized as a big value
	 * [1] = MinY. Initizalized as a big value
	 * [2] = MaxX. Initizalized as a small value
	 * [3] = MaxY. Initizalized as a small value
	 */
	annotation_extremes[0] = BIG_VALUE;
	annotation_extremes[1] = BIG_VALUE;
	annotation_extremes[2] = SMALL_VALUE;
	annotation_extremes[3] = SMALL_VALUE;
}

/*
 * Method Overview: Adds a new point to the existing line
 * Parameters: (x,y) coordinates of the point to add
 * Return: None
 */
void LineAnnotation::addPoint(long double x, long double y)
{
	myPoints.push_back(x);
	myPoints.push_back(y);

	//Checks if x value is lower than min x value
	if(x<annotation_extremes[0])
	{
		annotation_extremes[0] = x;
	}
	//Checks if y value is lower than min y value
	if(y<annotation_extremes[1])
	{
		annotation_extremes[1] = y;
	}
	//Checks if x value is higher than max x value
	if(x>annotation_extremes[2])
	{
		annotation_extremes[2] = x;
	}
	//Checks if y value is higher than max y value
	if(y>annotation_extremes[3])
	{
		annotation_extremes[3] = y;
	}

	recalculateCenter();
}

/*
 * Method Overview: Return the points of the line
 * Parameters: None
 * Return: Vector that contains the points of the line
 */
vector<long double>* LineAnnotation::getPoints()
{
	return &myPoints;
}