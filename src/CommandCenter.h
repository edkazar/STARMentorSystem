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
 * Name: CommandCenter.h
 *
 * Overview: This class is the one in charge of controling the flow
 * of the program. Almost every other manager code makes a call to 
 * this code before perforfming an action, this because they need 
 * to know the current state of the program.
 */
///////////////////////////////////////////////////////////////////

//Define guards
#ifndef COMMAND_CENTER_H
#define COMMAND_CENTER_H

//---------------------------Includes----------------------------//
#include <vector>//Enable the usage of the vector class

class CommandCenter
{
public:
	//-------------------------Methods---------------------------//
	CommandCenter();//Class Constructor

	//Gets the annotation panel shown flag
	int getAnnotationPanelShownFlag();

	//Changes the state of the annotation panel shown flag
	void setAnnotationPanelShownFlag(int pFlag);

	//Gets the points drawable flag
	int getPointsDrawableFlag();

	//Changes the state of the annotation panel shown flag
	void setPointsDrawableFlag(int pFlag);

	//Gets the annotation panel shown flag
	int getLinesDrawableFlag();

	//Changes the state of the annotation panel shown flag
	void setLinesDrawableFlag(int pFlag);

	//Gets the line drawn received flag
	int getLineDrawnFlag();

	//Changes the state of the line drawn flag
	void setLineDrawnFlag(int pFlag);

	//Gets the roi drawn flag
	int getRoiDrawnFlag();

	//Changes the state of the roi drawn flag
	void setRoiDrawnFlag(int pFlag);

	//Gets the annotation command received flag
	int getAnnotationCommandFlag();

	//Changes the state of the annotation command received flag
	void setAnnotationCommandFlag(int pFlag);

	//Retreives the command set by other manager
	int getAnnotationCommand();

	//Sets a command to be performed by the AnnotationManager
	void setAnnotationCommand(int pCommand);

	//Gets the virtual annotation creation flag
	int getVirtualAnnotationCreationFlag();

	//Changes the state of the virtual annotation creation flag
	void setVirtualAnnotationCreationFlag(int pFlag);

	//Gets the line selected flag
	int getLineSelectedFlag();

	//Changes the state of the line selected flag
	void setLineSelectedFlag(int pFlag);

	//Gets the virtual annotation selected flag
	int getVirtualAnnotationSelectedFlag();

	//Changes the state of the virtual annotation selected flag
	void setVirtualAnnotationSelectedFlag(int pFlag);

	//Retreives the values set by other manager
	std::vector<int> getSelectedIDs();

	//Sets a command to be performed by the AnnotationManager
	void setSelectedIDs(std::vector<int> pVectorID);

	//Gets the JSON creation flag
	int getJSONCreationFlag();

	//Changes the state of the JSON creation flag
	void setJSONCreationFlag(int pFlag);

	//------------------------Variables--------------------------//
	//None

private:
	//-------------------------Methods---------------------------//
	//None

	//------------------------Variables--------------------------//
	//Annotation panel shown flag
	int AnnotationPanelShown;

	//Points drawable flag
	int PointsDrawable;

	//Lines drawable flag
	int LinesDrawable;

	//Flag to indicate if a line is being drawn
	int LineDrawn;

	//Flag to indicate is a roi is being drawn
	int RoiDrawn;

	//Annotation manager command needed flag
	int AnnotationCommandReceived;

	//Code of the Annotation Command
	int AnnotationCommandCode;

	//Virtual annotation creation flag
	int VirtualAnnotationCreation;

	//Line selected flag
	int LineSelected;

	//Virtual annotation selected flag
	int VirtualAnnotationSelected;

	//Contains the selected IDs at the moment
	std::vector<int> SelectedIDs;

	//JSON Creation flag
	int JSONCreation;
};

#endif