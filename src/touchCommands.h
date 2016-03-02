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
 * Name: touchCommands.h
 *
 * Overview: Interface that contains the standard codes for the 
 * correct interpretation of touch based events. Each event has a
 * assign numerical value that will be used to easily understand 
 * the code.
 */
///////////////////////////////////////////////////////////////////

//Define guards
#ifndef TOUCHCOMMANDS_H
#define TOUCHCOMMANDS_H

//Clockwise rotation code
#ifndef ROTATE_CLK
#define ROTATE_CLK 1
#endif

//Counter-Clockwise rotation code
#ifndef ROTATE_CNTR_CLK
#define ROTATE_CNTR_CLK 2
#endif

//Zoom in code
#ifndef ZOOM_IN
#define ZOOM_IN 3
#endif

//Zoom out code
#ifndef ZOOM_OUT
#define ZOOM_OUT 4
#endif

//Translate right code
#ifndef TRANSLATE_RIGHT
#define TRANSLATE_RIGHT 5
#endif

//Translate left code
#ifndef TRANSLATE_LEFT
#define TRANSLATE_LEFT 6
#endif

//Translate up code
#ifndef TRANSLATE_UP
#define TRANSLATE_UP 7
#endif

//Translate down code
#ifndef TRANSLATE_DOWN
#define TRANSLATE_DOWN 8
#endif

//Add line to map line code
#ifndef ADD_LINE
#define ADD_LINE 9
#endif

//Add point to current line code
#ifndef ADD_POINT
#define ADD_POINT 10
#endif

//Clear current line buffer code
#ifndef CLEAR_LINE
#define CLEAR_LINE 11
#endif

//Add point to current line code
#ifndef ADD_POINT_ANNOTATION
#define ADD_POINT_ANNOTATION 12
#endif

#endif // TOUCHCOMMANDS_H