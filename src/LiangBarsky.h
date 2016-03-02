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
 * Name: LiangBarsky.h
 *
 * Overview: This code is used to ensure that that every line
 * created by the Bressenham program will be contained in the
 * window of it. The algorithm selects which lines should be
 * drawn, and whether or not modify them for this purpose.
 * This code was adapted from Hin Jang's C++ implementation:
 * http://hinjang.com/articles/04.html#eight
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

//Define guards
#ifndef LIANG_BARSKY_H__
#define LIANG_BARSKY_H__

class LiangBarsky
{
public:
	//-------------------------Methods---------------------------//
	//Class Constructor
	LiangBarsky(int win_x1, int win_y1, int win_x2,  int win_y2);

	//Modifies parameters in place to clip the line
	int clip_line(int *x1, int *y1, int *x2,  int *y2);

	//------------------------Variables--------------------------//
	//None

private:
	//-------------------------Methods---------------------------//
	//Determines if the input number is zero
	int is_zero(float v);

	//Determines if a point is inside the clipping window
	int point_inside(int x, int y);

	//Calcules the intersection of number with the clipping window
	int clipT(float num, float denom, float *tE, float *tL);

	//------------------------Variables--------------------------//
	//Clipping window
	float liang_barsky_clip_window[4];
};
#endif