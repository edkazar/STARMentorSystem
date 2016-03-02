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
 * Name: annotationCommands.h
 *
 * Overview: Interface that contains the interpretation of the 
 * commands received by the GUI and to be performed by the manager
 * of the annotation process. This is used to preserve the code as
 * modular as possible.
 */
///////////////////////////////////////////////////////////////////

//Define guards
#ifndef ANNOTATIONCOMMANDS_H
#define ANNOTATIONCOMMANDS_H

//deselect all lines command
#ifndef DESELECT_ALL_LINES
#define DESELECT_ALL_LINES 1
#endif

//clear all lines
#ifndef CLEAR_ALL_LINES
#define CLEAR_ALL_LINES 2
#endif

//Erase selected lines command
#ifndef ERASE_LINES
#define ERASE_LINES 3
#endif

//End OpenGL context command
#ifndef END_OPENGL_CONTEXT
#define END_OPENGL_CONTEXT 4
#endif

#endif // ANNOTATIONCOMMANDS_H