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
 * Name: LiangBarsky.cpp
 *
 * Overview: .cpp of LiangBarsky.h
 *
 * This code is free software; you can redistribute it and/or 
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * It is being distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 */
///////////////////////////////////////////////////////////////////

//Include its header file
#include "LiangBarsky.h"

/*
 * Method Overview: Constructor of the class
 * Parameters: Clipping windows coordinates
 * Return: Instance of the class
 */
LiangBarsky::LiangBarsky(int win_x1, int win_y1, int win_x2,  int win_y2)
{
	liang_barsky_clip_window[0] = (float)win_x1;
	liang_barsky_clip_window[1] = (float)win_y1;
	liang_barsky_clip_window[2] = (float)win_x2;
	liang_barsky_clip_window[3] = (float)win_y2;
}

/*
 * Method Overview: Determines if a float number is zero
 * Parameters: Number to  analyze
 * Return: Whether or not the number is zero
 */
int LiangBarsky::is_zero(float v)
{
	return (v > -0.000001f && v < 0.000001f);
}

/*
 * Method Overview: Checks if a point is inside the clipping window
 * Parameters: Clipping window, point to analyze
 * Return: Whether or not the point is inside the clipping window
 */
int LiangBarsky::point_inside(int x, int y)
{
	return (x >= liang_barsky_clip_window[0] && x <= liang_barsky_clip_window[2] &&
		y >= liang_barsky_clip_window[1] && y <= liang_barsky_clip_window[3]);
}

/*
 * Method Overview: Determine the point-window intersection
 * Parameters (1): Coordinate to intersect
 * Parameters (2): Distance between final and initial coordinates
 * Parameters (3): varaibles for the Liang Barsky algorithm
 * Return: Flag to indicate success
 */
int LiangBarsky::clipT(float num, float denom, float *tE, float *tL)
{
	float t;
	
	//Determine if it is a single point
	if (is_zero(denom))
		return num < 0.0;

	//Calculates the step
	t = num / denom;

	//Modifies (or not) the value of the variables
	if (denom > 0) {
		if (t > *tL)
			return 0;
		if (t > *tE)
			*tE = t;
	} else {
		if (t < *tE)
			return 0;
		if (t < *tL)
			*tL = t;
	}
	return 1;
}

/*
 * Method Overview: Modifies received parameters to clip the line
 * Parameters: Clipping window, (Xin,Yin),(Xfin,Yfin) line-to-clip
 * Return (1): 0 if line is totally outside clip window
 * Return (2): 1 if line is not totally outside clip window
 */
int LiangBarsky::clip_line(int *x1, int *y1, int *x2,  int *y2)
{
	float dx, dy, tE, tL;

	//Distance between the final and initial coordinates
	dx = (float)(*x2 - *x1);
	dy = (float)(*y2 - *y1);

	//Determines if it is a single point and if it is inside
	if (is_zero(dx) && is_zero(dy) && point_inside(*x1, *y1))
		return 1;

	tE = 0;
	tL = 1;

	//Intersection with the window (see Liang-Barsky theory)
	if (clipT(liang_barsky_clip_window[0] - (float) *x1,  dx, &tE, &tL) &&
		clipT((float) *x1 - liang_barsky_clip_window[2], -dx, &tE, &tL) &&
		clipT(liang_barsky_clip_window[1] - (float) *y1,  dy, &tE, &tL) &&
		clipT((float) *y1 - liang_barsky_clip_window[3], -dy, &tE, &tL)) {
		if (tL < 1) {
			*x2 = (int) ((float) *x1 + tL * dx);
			*y2 = (int) ((float) *y1 + tL * dy);
		}
		if (tE > 0) {
			*x1 += (int)(tE * dx);
			*y1 += (int)(tE * dy);
		}
		return 1;
	}
	return 0;
}