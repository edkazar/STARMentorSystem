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
 * Name: Mapping.h
 *
 * Overview: This code maps a line in the 2D space to the first
 * octant of it. It is used as a easy way to solve some of the
 * constraints of Bressenham's Line Algorithm when working in
 * octants that are not the first one.
 */
///////////////////////////////////////////////////////////////////

#ifndef MAPPING_H
#define MAPPING_H

//---------------------------Includes----------------------------//
#include <stdlib.h>

class Mapping
{
public:
	//---------------------------Methods-----------------------------//
	//Class constructor
	Mapping();

	//Identifies in which octant a line is
	void octants(int number[],int controls[]);

	//Maps the line to  the first octant
	void mapping(int number[],int controls[]);

	//Maps the line to its orignal octant
	void demapping(int number[],int controls[],int orgX, int orgY);

	//------------------------Variables--------------------------//
	//None
};
#endif // MAPPING_H
