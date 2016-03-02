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
 * Name: AnnotationsManager.h
 *
 * Overview: This code uses the OpenGL Libraries methods to create
 * a window in which the image obtained from the OpenCV class will
 * be shown. It also can superimpose annotations created either by
 * touchs events or by keyboard events.
 */
///////////////////////////////////////////////////////////////////

//---------------------------Includes----------------------------//
#include <GL\glew.h>//Glew Standard Library
#include <GL\freeglut.h>//Freeglut Standard Library
#include <vector>//Enable the usage of the vector class
#include <map>//Map Library
#include <math.h>//Enable the usage of math algorithms
#include <opencv2/opencv.hpp>//OpenCV Core Library
#include "CommandCenter.h"//General Program Flow Controller
#include "JSONManager.h"//JSON Type Objects Creator
#include "LineAnnotation.h"//Basic Line Annotation Structure
#include "Mapping.h"//Cuadrants translation code
#include "LiangBarsky.h"//Window clipping algorithm code
#include "touchCommands.h"//Touch events standard commands
#include "annotationCommands.h"//Annotation-related commands
#include "JSONDefinitions.h"////General JSON definitions

using namespace std;//Standard Library

//--------------------------Functions----------------------------//
//Rounds a number
long double round(long double number);

//Adds a point to a line that is currently being created
void addPoint(int id, long double x, long double y);

//Changes the color of an specific position in the framebuffer
void plot(int posX, int posY, int selected_state);

//Bressenham line algorithm for line creation
void bressenham(int Xin, int Yin, int Xfin, int Yfin, int Xorg, int Yorg, int controls[], int selected_state);

//Checks if a line crosses the X axis
int crossingLine(long double Xin, long double Yin,long double Xfin, long double Yfin, int* wasException);

//Clean the buffer, allowing lines to not be permanently drawn 
void cleanBuffer();

//Geometrical transformation: translate
void translate(long double transX, long double transY);

//Geometrical transformation: zoom
void zoom(long double scale);

//Process by which a line is rotated
void rotate(long double rad);

//Geometrical transformation: rotate
void pointRotation(long double X, long double Y, long double transX,long double transY,long double angle,
				   long double origX, long double origY, long double* rotated_values);

//Calls all the necessary methods for line drawing
void drawLines();

//Edit the frambuffer with keyboard events
void keyboard(unsigned char key, int x, int y);

//Method used to erase the currently selected lines
void eraseSelectedLines();

//Method used to deselect all lines 
void deselectAllLines();

//Erases all the lines
void clearAllLines();

//Terminates the program by killing the OpenGL thread
void endOpenGLContext();

//Checks and interprets a command send by the CommandCenter
void checkAndInterpretCommand();

//Routine to start the JSON creation process
void createJSONLineMessage(string command, LineAnnotation* annotation);

//Gives the signal to start the creation of JSON UpdateCommands
void startJSONLineUpdate();

//Edit the frambuffer with touch events
void OpenGLtouchControls(int command, int id, long double x, long double y);

//Assings an image matrix to be the background image of the window
void setOpenCVImage(cv::Mat image);

//Returns recently added line
char* OpenGLgetNewLine(int id);

//Variant of the point inside of polygon algorithm
int pointInPolygon(vector<long double> roi_extremes);

//Assings the values of the framebuffer to the window's background
void draw_scene();

//Refresh the window by calling OpenGL methods
void refresh();

//Inits framebuffer and the OpenGL environment
void initWindow(int argc, char* argv[], int resX, int resY, CommandCenter* pCommander, JSONManager* pJSON);