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
 * Name: GUIDefinitions.h
 *
 * Overview: Interface that contains the required definitions for
 * the GUI creation process. This code is highly dependant on the
 * screen being used by the MentorSystem (as the GUI image itself).
 * Therefore, changing the monitor will required to modify the
 * values written in this file (or creating the new GUI images even
 * more screen-wired).
 */
///////////////////////////////////////////////////////////////////

//Define guards
#ifndef GUI_DEFINITIONS_H
#define GUI_DEFINITIONS_H

//--------------------Images Path Definitions--------------------//
//Path to the Button Points On image
#ifndef BUTTON_POINTS_ON_PATH
#define BUTTON_POINTS_ON_PATH "../images/ButtonPointsOn.png"
#endif

//Path to the Button Points Off image
#ifndef BUTTON_POINTS_OFF_PATH
#define BUTTON_POINTS_OFF_PATH "../images/ButtonPointsOff.png"
#endif

//Path to the Lines On image
#ifndef BUTTON_LINES_ON_PATH
#define BUTTON_LINES_ON_PATH "../images/ButtonLinesOn.png"
#endif

//Path to the Button Points On image
#ifndef BUTTON_LINES_OFF_PATH
#define BUTTON_LINES_OFF_PATH "../images/ButtonLinesOff.png"
#endif

//Path to the Button Clear All image
#ifndef BUTTON_CLEAR_PATH
#define BUTTON_CLEAR_PATH "../images/ButtonClearAll.png"
#endif

//Path to the Button Erase image
#ifndef BUTTON_ERASE_PATH
#define BUTTON_ERASE_PATH "../images/ButtonErase.png"
#endif

//Path to the Button Exit image
#ifndef BUTTON_EXIT_PATH
#define BUTTON_EXIT_PATH "../images/ButtonExit.png"
#endif

//Path to the Annotation Panel image
#ifndef ANNOTATION_PANEL_PATH
#define ANNOTATION_PANEL_PATH "../images/AnnotationPanel.png"
#endif

//Path to the Annotation Panel Hidden image
#ifndef ANNOTATION_PANEL_HIDDEN_PATH
#define ANNOTATION_PANEL_HIDDEN_PATH "../images/AnnotationPanelHidden.png"
#endif

//--------------------General GUI Definitions--------------------//
//Zero X and Y coordinates of the screen
#ifndef SCREEN_ORIGIN
#define SCREEN_ORIGIN 0
#endif

//Size of the buttons' .png
#ifndef BUTTON_SIZE
#define BUTTON_SIZE 108
#endif

//Error margin of the buttons' .png
#ifndef ERROR_MARGIN
#define ERROR_MARGIN 43
#endif

//Point Button Min X
#ifndef POINT_BUTTON_MIN_X
#define POINT_BUTTON_MIN_X 65
#endif

//Point Button Min Y
#ifndef POINT_BUTTON_MIN_Y
#define POINT_BUTTON_MIN_Y 20
#endif

//Point Button Max X
#ifndef POINT_BUTTON_MAX_X
#define POINT_BUTTON_MAX_X 135
#endif

//Point Button Max Y
#ifndef POINT_BUTTON_MAX_Y
#define POINT_BUTTON_MAX_Y 90
#endif

//Line Button Min X
#ifndef LINE_BUTTON_MIN_X
#define LINE_BUTTON_MIN_X 170
#endif

//Line Button Min Y
#ifndef LINE_BUTTON_MIN_Y
#define LINE_BUTTON_MIN_Y 20
#endif

//Line Button Max X
#ifndef LINE_BUTTON_MAX_X
#define LINE_BUTTON_MAX_X 240
#endif

//Line Button Max Y
#ifndef LINE_BUTTON_MAX_Y
#define LINE_BUTTON_MAX_Y 90
#endif

//Clear All Button Min X
#ifndef CLEAR_BUTTON_MIN_X
#define CLEAR_BUTTON_MIN_X 1830
#endif

//Clear All Button Min Y
#ifndef CLEAR_BUTTON_MIN_Y
#define CLEAR_BUTTON_MIN_Y 990
#endif

//Clear All Button Max X
#ifndef CLEAR_BUTTON_MAX_X
#define CLEAR_BUTTON_MAX_X 1900
#endif

//Clear All Button Max Y
#ifndef CLEAR_BUTTON_MAX_Y
#define CLEAR_BUTTON_MAX_Y 1060
#endif

//Erase Button Min X
#ifndef ERASE_BUTTON_MIN_X
#define ERASE_BUTTON_MIN_X 1830
#endif

//Erase Button Min Y
#ifndef ERASE_BUTTON_MIN_Y
#define ERASE_BUTTON_MIN_Y 885
#endif

//Erase Button Max X
#ifndef ERASE_BUTTON_MAX_X
#define ERASE_BUTTON_MAX_X 1900
#endif

//Erase Button Max Y
#ifndef ERASE_BUTTON_MAX_Y
#define ERASE_BUTTON_MAX_Y 955
#endif

//Exit Button Min X
#ifndef EXIT_BUTTON_MIN_X
#define EXIT_BUTTON_MIN_X 1830
#endif

//Exit Button Min Y
#ifndef EXIT_BUTTON_MIN_Y
#define EXIT_BUTTON_MIN_Y 20
#endif

//Exit Button Max X
#ifndef EXIT_BUTTON_MAX_X
#define EXIT_BUTTON_MAX_X 1900
#endif

//Exit Button Max Y
#ifndef EXIT_BUTTON_MAX_Y
#define EXIT_BUTTON_MAX_Y 90
#endif

//Closed Panel Tab Min X
#ifndef	CLOSED_PANEL_TAB_MIN_X
#define CLOSED_PANEL_TAB_MIN_X 0
#endif

//Closed Panel Tab Min Y
#ifndef CLOSED_PANEL_TAB_MIN_Y
#define CLOSED_PANEL_TAB_MIN_Y 515
#endif

//Closed Panel Tab Max X
#ifndef CLOSED_PANEL_TAB_MAX_X
#define CLOSED_PANEL_TAB_MAX_X 28
#endif

//Closed Panel Tab Max Y
#ifndef CLOSED_PANEL_TAB_MAX_Y
#define CLOSED_PANEL_TAB_MAX_Y 640
#endif

//Open Panel Tab Min X
#ifndef OPEN_PANEL_TAB_MIN_X
#define OPEN_PANEL_TAB_MIN_X 272
#endif

//Open Panel Tab Min Y
#ifndef OPEN_PANEL_TAB_MIN_Y
#define OPEN_PANEL_TAB_MIN_Y 515
#endif

//Open Panel Tab Max X
#ifndef OPEN_PANEL_TAB_MAX_X
#define OPEN_PANEL_TAB_MAX_X 300
#endif

//Open Panel Tab Max Y
#ifndef OPEN_PANEL_TAB_MAX_Y
#define OPEN_PANEL_TAB_MAX_Y 640
#endif

//--------------Annotation Panel Margins Definitions-------------//
//First row upper margin
#ifndef FIRST_ROW_UPPER_MARGIN
#define FIRST_ROW_UPPER_MARGIN 189
#endif

//First row lower margin
#ifndef FIRST_ROW_LOWER_MARGIN
#define FIRST_ROW_LOWER_MARGIN 263
#endif

//Second row upper margin
#ifndef SECOND_ROW_UPPER_MARGIN
#define SECOND_ROW_UPPER_MARGIN 267
#endif

//Second row lower margin
#ifndef SECOND_ROW_LOWER_MARGIN
#define SECOND_ROW_LOWER_MARGIN 341
#endif

//Third row upper margin
#ifndef THIRD_ROW_UPPER_MARGIN
#define THIRD_ROW_UPPER_MARGIN 345
#endif

//Third row lower margin
#ifndef THIRD_ROW_LOWER_MARGIN
#define THIRD_ROW_LOWER_MARGIN 419
#endif

//Fourth row upper margin
#ifndef FOURTH_ROW_UPPER_MARGIN
#define FOURTH_ROW_UPPER_MARGIN 423
#endif

//Fourth row lower margin
#ifndef FOURTH_ROW_LOWER_MARGIN
#define FOURTH_ROW_LOWER_MARGIN 497
#endif

//Fifth row upper margin
#ifndef FIFTH_ROW_UPPER_MARGIN
#define FIFTH_ROW_UPPER_MARGIN 657
#endif

//Fifth row lower margin
#ifndef FIFTH_ROW_LOWER_MARGIN
#define FIFTH_ROW_LOWER_MARGIN 731
#endif

//Sixth row upper margin
#ifndef SIXTH_ROW_UPPER_MARGIN
#define SIXTH_ROW_UPPER_MARGIN 891
#endif

//Sixth row lower margin
#ifndef SIXTH_ROW_LOWER_MARGIN
#define SIXTH_ROW_LOWER_MARGIN 965
#endif

//Seventh row upper margin
#ifndef SEVENTH_ROW_UPPER_MARGIN
#define SEVENTH_ROW_UPPER_MARGIN 969
#endif

//Seventh row lower margin
#ifndef SEVENTH_ROW_LOWER_MARGIN
#define SEVENTH_ROW_LOWER_MARGIN 1043
#endif

//First column left margin
#ifndef FIRST_COLUMN_LEFT_MARGIN
#define FIRST_COLUMN_LEFT_MARGIN 36
#endif

//First column right margin
#ifndef FIRST_COLUMN_RIGHT_MARGIN
#define FIRST_COLUMN_RIGHT_MARGIN 110
#endif

//Second column left margin
#ifndef SECOND_COLUMN_LEFT_MARGIN
#define SECOND_COLUMN_LEFT_MARGIN 114
#endif

//Second column right margin
#ifndef SECOND_COLUMN_RIGHT_MARGIN
#define SECOND_COLUMN_RIGHT_MARGIN 188
#endif

//Third column left margin
#ifndef THIRD_COLUMN_LEFT_MARGIN
#define THIRD_COLUMN_LEFT_MARGIN 192
#endif

//First column right margin
#ifndef THIRD_COLUMN_RIGHT_MARGIN
#define THIRD_COLUMN_RIGHT_MARGIN 266
#endif

#endif