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
 * Name: CommandCenter.cpp
 *
 * Overview: .cpp of CommandCenter.h
 */
///////////////////////////////////////////////////////////////////

//Include its header file
#include "CommandCenter.h"

/*
 * Method Overview: Constructor of the class
 * Parameters: None
 * Return: Instance of the class
 */
CommandCenter::CommandCenter()
{
	AnnotationPanelShown = 0;

	PointsDrawable = 0;

	LinesDrawable = 0;

	LineDrawn = 0;

	RoiDrawn = 0;

	AnnotationCommandReceived = 0;

	VirtualAnnotationCreation = 0;

	LineSelected = 0;

	VirtualAnnotationSelected = 0;

	JSONCreation = 0;
}

/*
 * Method Overview: Retrieves the annotation panel shown flag
 * Parameters: None
 * Return: Annotation panel shown flag
 */
int CommandCenter::getAnnotationPanelShownFlag()
{
	return AnnotationPanelShown;
}

/*
 * Method Overview: Sets the annotation panel shown flag
 * Parameters: Value to set the flag to
 * Return: None
 */
void CommandCenter::setAnnotationPanelShownFlag(int pFlag)
{
	AnnotationPanelShown = pFlag;
}

/*
 * Method Overview: Retrieves the points drawable flag
 * Parameters: None
 * Return: Points drawable flag
 */
int CommandCenter::getPointsDrawableFlag()
{
	return PointsDrawable;
}

/*
 * Method Overview: Sets the points drawable flag
 * Parameters: Value to set the flag to
 * Return: None
 */
void CommandCenter::setPointsDrawableFlag(int pFlag)
{
	PointsDrawable = pFlag;
}

/*
 * Method Overview: Retrieves the lines drawable flag
 * Parameters: None
 * Return: Lines drawable flag
 */
int CommandCenter::getLinesDrawableFlag()
{
	return LinesDrawable;
}

/*
 * Method Overview: Sets the lines drawable flag
 * Parameters: Value to set the flag to
 * Return: None
 */
void CommandCenter::setLinesDrawableFlag(int pFlag)
{
	LinesDrawable = pFlag;
}

/*
 * Method Overview: Retrieves the line drawn flag
 * Parameters: None
 * Return: Line drawn flag
 */
int CommandCenter::getLineDrawnFlag()
{
	return LineDrawn;
}

/*
 * Method Overview: Sets the line drawn flag
 * Parameters: Value to set the flag to
 * Return: None
 */
void CommandCenter::setLineDrawnFlag(int pFlag)
{
	LineDrawn = pFlag;
}

/*
 * Method Overview: Retrieves the roi drawn flag
 * Parameters: None
 * Return: Roi drawn flag
 */
int CommandCenter::getRoiDrawnFlag()
{
	return RoiDrawn;
}

/*
 * Method Overview: Sets the roi drawn flag
 * Parameters: Value to set the flag to
 * Return: None
 */
void CommandCenter::setRoiDrawnFlag(int pFlag)
{
	RoiDrawn = pFlag;
}

/*
 * Method Overview: Retrieves the annotation command flag
 * Parameters: None
 * Return: Annotation command flag
 */
int CommandCenter::getAnnotationCommandFlag()
{
	return AnnotationCommandReceived;
}

/*
 * Method Overview: Sets the annotation command flag
 * Parameters: Value to set the flag to
 * Return: None
 */
void CommandCenter::setAnnotationCommandFlag(int pFlag)
{
	AnnotationCommandReceived = pFlag;
}

/*
 * Method Overview: Retrieves the annotation command
 * Parameters: None
 * Return: Value of the annotation command
 */
int CommandCenter::getAnnotationCommand()
{
	return AnnotationCommandCode;
}

/*
 * Method Overview: Sets the annotation command
 * Parameters: Value to set the annotation command to
 * Return: None
 */
void CommandCenter::setAnnotationCommand(int pCommand)
{
	AnnotationCommandCode = pCommand;
}

/*
 * Method Overview: Retrieves the virtual annotation creation flag
 * Parameters: None
 * Return: Value of the virtual annotation creation
 */
int CommandCenter::getVirtualAnnotationCreationFlag()
{
	return VirtualAnnotationCreation;
}

/*
 * Method Overview: Sets the virtual annotation creation flag
 * Parameters: Value to set the flag to
 * Return: None
 */
void CommandCenter::setVirtualAnnotationCreationFlag(int pFlag)
{
	VirtualAnnotationCreation = pFlag;
}

/*
 * Method Overview: Retrieves the line selected flag
 * Parameters: None
 * Return: Value of the line selected
 */
int CommandCenter::getLineSelectedFlag()
{
	return LineSelected;
}

/*
 * Method Overview: Sets the line selected flag
 * Parameters: Value to set the flag to
 * Return: None
 */
void CommandCenter::setLineSelectedFlag(int pFlag)
{
	LineSelected = pFlag;
}

/*
 * Method Overview: Retrieves the virtual annotation selected flag
 * Parameters: None
 * Return: Value of the virtual annotation selected
 */
int CommandCenter::getVirtualAnnotationSelectedFlag()
{
	return VirtualAnnotationSelected;
}

/*
 * Method Overview: Sets the virtual annotation selected flag
 * Parameters: Value to set the flag to
 * Return: None
 */
void CommandCenter::setVirtualAnnotationSelectedFlag(int pFlag)
{
	VirtualAnnotationSelected = pFlag;
}

/*
 * Method Overview: Retrieves the selected IDs list
 * Parameters: None
 * Return: Value of the selected IDs list
 */
std::vector<int> CommandCenter::getSelectedIDs()
{
	return SelectedIDs;
}

/*
 * Method Overview: Sets the list of selected IDs
 * Parameters: Value to set the list to
 * Return: None
 */
void CommandCenter::setSelectedIDs(std::vector<int> pVectorID)
{
	SelectedIDs = pVectorID;
}

/*
 * Method Overview: Retrieves the JSON creation flag
 * Parameters: None
 * Return: Value of the JSON creation flag
 */
int CommandCenter::getJSONCreationFlag()
{
	return JSONCreation;
}

/*
 * Method Overview: Sets the JSON creation flag
 * Parameters: Value to set the flag to
 * Return: None
 */
void CommandCenter::setJSONCreationFlag(int pFlag)
{
	JSONCreation = pFlag;
}