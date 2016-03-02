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
 * Name: AnnotationsManager.cpp
 *
 * Overview: .cpp of AnnotationsManager.h
 */
///////////////////////////////////////////////////////////////////

//Include its header file
#include "AnnotationsManager.h"

//--------------------------Definitions--------------------------//
#define ZERO 0.000001
#define ANNOTATION_RED 0.97
#define ANNOTATION_GREEN 1.0
#define ANNOTATION_BLUE 0.0
#define PI 3.14159265358979323846

//Define a RGB struct to have in position of the framebuffer
typedef struct {
	double r;
	double g;
	double b;
} COLOR;

//---------------------------Variables---------------------------//
//Screen resolution
int resolutionX, resolutionY;

//current Id of the line being drawn
int currentID = -1;

//Command Center instance
CommandCenter* myCommander;

//JSONManager instance
JSONManager* myJSON;

//Stores all the lines that are going to be drawn by Bressenham
map<int, LineAnnotation*> lines; 

//Stores the Ids of the line that are inside of a specific roi
vector<int> selected_lines_id;

//Stores the points of a the line currently being created
LineAnnotation* temp_line=NULL;

//Framebuffer. It has the RGB values of the whole shown window
COLOR **buffer;

//Clipping Manager instance
LiangBarsky* my_clip_window;

//Map Manager instance
Mapping* MapManager;

//--------------------------Functions----------------------------//
/*
 * Method Overview: Method to round a number
 * Parameters: Number to be rounded
 * Return: Rounded number
 */
long double round(long double number)
{
    return number < 0.0 ? ceil(number - 0.5) : floor(number + 0.5);
}

/*
 * Method Overview: Adds point to the line currently being created
 * Parameters: Line ID, X and Y coordinates of the point to add
 * Return: None
 */
void addPoint(int id,long double x, long double y)
{
	//if it receives a new line ID
	if(currentID!=id)
	{
		temp_line = new LineAnnotation(id);
		currentID = id;
	}
	//Adds the new point
	temp_line->addPoint(x,abs(y-resolutionY));

	/*
	 * Adds the temporal line to the line vector
	 * This is done in order to draw the line as soon as the
	 * touch event is received
	 */
    lines.insert(pair<int, LineAnnotation*>(id, temp_line));
}

/*
 * Method Overview: Changes the color of a pixel in the framebuffer
 * Parameters: Pixel X and Y coordinates
 * Return: None
 */
void plot(int posX, int posY, int selected_state)
{
	//Multiple assignments are done to create a thicker line
	if(posX-1 > ZERO)
	{
		buffer[posX-1][posY].r = ANNOTATION_RED;
		if(!selected_state)
		{
			buffer[posX-1][posY].g = ANNOTATION_GREEN;
		}
		else
		{
			buffer[posX-1][posY].g = ANNOTATION_BLUE;
		}
		buffer[posX-1][posY].b = ANNOTATION_BLUE;
	}

	if(posY-1 > ZERO)
	{
		buffer[posX][posY-1].r = ANNOTATION_RED;
		if(!selected_state)
		{
			buffer[posX][posY-1].g = ANNOTATION_GREEN;
		}
		else
		{
			buffer[posX][posY-1].g = ANNOTATION_BLUE;
		}
		buffer[posX][posY-1].b = ANNOTATION_BLUE;
	}

	buffer[posX][posY].r = ANNOTATION_RED;
	if(!selected_state)
	{
		buffer[posX][posY].g = ANNOTATION_GREEN;
	}
	else
	{
		buffer[posX][posY].g = ANNOTATION_BLUE;
	}
	buffer[posX][posY].b = ANNOTATION_BLUE;
	
	if(posX+1 < resolutionX)
	{
		buffer[posX+1][posY].r = ANNOTATION_RED;
		if(!selected_state)
		{
			buffer[posX+1][posY].g = ANNOTATION_GREEN;
		}
		else
		{
			buffer[posX+1][posY].g = ANNOTATION_BLUE;
		}
		buffer[posX+1][posY].b = ANNOTATION_BLUE;
	}

	if(posY+1 < resolutionY)
	{
		buffer[posX][posY+1].r = ANNOTATION_RED;
		if(!selected_state)
		{
			buffer[posX][posY+1].g = ANNOTATION_GREEN;
		}
		else
		{
			buffer[posX][posY+1].g = ANNOTATION_BLUE;
		}
		buffer[posX][posY+1].b = ANNOTATION_BLUE;
	}

}

/*
 * Method Overview: Bressenham Line Drawing Algorithm
 * Parameters (1): (X,Y) initial and final coordinates of the line
 * Parameters (2): (X,Y) original coordinates before being mapped
 * Parameters (3): the int array indicates how mapping was done 
 * Parameters (4): whereas or not the line is currently selected
 * Return: None
 */
void bressenham(int Xin, int Yin, int Xfin, int Yfin, int Xorg, int Yorg, int controls[], int selected_state)
{
	//Array to store demapped values
	int demap[2];

	//Variables used by the algorithm
	int delta_E, delta_NE, d, Xp, Yp;

	//Calculates the initial step (see Bresseham theory)
	delta_E = 2*(Yfin-Yin);
	delta_NE = 2*((Yfin-Yin)-(Xfin-Xin));

	//Assigns the initial points as the first value
	Xp = Xin; Yp = Yin;

	//Gets the values need to be demapped
	demap[0] = (int)Xp;
    demap[1] = (int)Yp;

	//Demaps the values obtained
    MapManager->demapping(demap,controls,Xorg,Yorg);

	//Change the color of pixels in this position to draw line
	plot(demap[0],demap[1],selected_state);

	//Calculates the next delta (see Bresseham theory)
	d = 2*(Yfin-Yin)-(Xfin-Xin);

	//Iterates while the current point is not the last point
	while (Xp < Xfin)
	{
		//draw E (see Bresseham theory)
		if (d <= 0)
		{
			Xp++;
			d += delta_E;
		}
		//draw NE (see Bresseham theory)
		else
		{
			Xp++; Yp++;
			d += delta_NE;
		}	

		//Gets the values need to be demapped
		demap[0] = Xp;
		demap[1] = Yp;

		//Demaps the values obtained
		MapManager->demapping(demap,controls,Xorg,Yorg);

		//Change the color of pixels in this position to draw line
		plot(demap[0],demap[1],selected_state);
	}
}

/*
 * Method Overview: Method used to see if a line crosses the X axis
 * Parameters (1): Initial and final line-in-analysis coordiantes
 * Parameters (2): Generated exception code from the last run
 * Return: Whereas the point is inside of the region or not
 */
int crossingLine(long double Xin, long double Yin,long double Xfin, long double Yfin, int* wasException)
{
	int cross = 1;

	if(wasException[0]!=0)
	{
		if(wasException[0]==1)
		{
			if(Yfin < ZERO)
			{
				cross = 0;
			}
		}
		else
		{
			if(Yfin > ZERO)
			{
				cross = 0;
			}
		}
		wasException[0] = 0;
	}

	if(Xin < ZERO && Xfin < ZERO)
	{
		cross = 0;
	}
	else if(Yin < ZERO && Yfin < ZERO)
	{
		cross = 0;
	}
	else if(Yin > ZERO && Yfin > ZERO)
	{
		cross = 0;
	}
	else if((Yfin - ZERO) < ZERO)
	{
		if(Yin < ZERO)
		{
			wasException[0] = 1;
		}
		else
		{
			wasException[0] = 2;
		}
	}
	
	return cross;
}

/*
 * Method Overview: Cleans the buffer show just the right lines
 * Parameters: None
 * Return: None
 */
void cleanBuffer()
{
	int i, j;

	//Loops through the scene
	for (i = 0; i < resolutionX; i++) 
	{
		for (j = 0; j < resolutionY; j++) 
		{
			//Assings the color of the closest pixel
			int annotation_green = (buffer[i][j].g == ANNOTATION_GREEN || buffer[i][j].g == ANNOTATION_BLUE);
			if(buffer[i][j].r == ANNOTATION_RED && annotation_green && buffer[i][j].b == ANNOTATION_BLUE)
			{
				if(i-1 > ZERO)
				{
					buffer[i][j].r = buffer[i-1][j].r;
					buffer[i][j].g = buffer[i-1][j].g;
					buffer[i][j].b = buffer[i-1][j].b;
				}
				else
				{
					buffer[i][j].r = buffer[i+1][j].r;
					buffer[i][j].g = buffer[i+1][j].g;
					buffer[i][j].b = buffer[i+1][j].b;
				}
			}
		}
	}
}

/*
 * Method Overview: Translates the lines by an specific amount
 * Parameters: X and Y translation amounts
 * Return: None
 */
void translate(long double transX, long double transY)
{
	int i, j;

	//Loop through all the lines
	for (i = 0; i < (int)selected_lines_id.size(); i++) 
	{
		LineAnnotation* to_transf = lines.find(selected_lines_id.at(i))->second;

		for (j = 0; j < (int)((to_transf)->getPoints())->size(); j = j+2) 
        {
			//Adds the translation amount
			((to_transf)->getPoints())->at(j) += transX;
			((to_transf)->getPoints())->at(j+1) += transY;
        }
		//changs the extreme values of the line
		(to_transf->getExtremePoints())[0] += transX;
		(to_transf->getExtremePoints())[1] += transY;
		(to_transf->getExtremePoints())[2] += transX;
		(to_transf->getExtremePoints())[3] += transY;

		//calls the function to recalculate the center
		to_transf->recalculateCenter();
    }
}

/*
 * Method Overview: Zooms the lines by an specific amount
 * Parameters: Zoom amount
 * Return: None
 */
void zoom(long double scale)
{
	int i, j;
	
	long double general_center_X = 0.0;
	long double general_center_Y = 0.0;

	//calculates the general center of a group of lines
	for (i = 0; i < (int)selected_lines_id.size(); i++) 
	{
		general_center_X += (lines.find(selected_lines_id.at(i))->second)->getAnnotationCenter()[0];
		general_center_Y += (lines.find(selected_lines_id.at(i))->second)->getAnnotationCenter()[1];
	}

	general_center_X = general_center_X/(long double)selected_lines_id.size();
	general_center_Y = general_center_Y/(long double)selected_lines_id.size();

	//Loop through all the lines
	for (i = 0; i < (int)selected_lines_id.size(); i++) 
	{
		LineAnnotation* to_transf = lines.find(selected_lines_id.at(i))->second;

		for (j = 0; j < (int)((to_transf)->getPoints())->size(); j = j+2) 
        {
			/*
			 * Translates the point to the center of the scene
			 * Multiplies by zoom value
			 * Retranslates the point to its new zoomed value 
			 */
			((to_transf)->getPoints())->at(j) = ((((to_transf)->getPoints())->at(j) - 
				(general_center_X))*scale)+(general_center_X);
			((to_transf)->getPoints())->at(j+1) = ((((to_transf)->getPoints())->at(j+1) - 
				(general_center_Y))*scale)+(general_center_Y);
        }
		//changes the extreme values of the line
		(to_transf->getExtremePoints())[0] = (((to_transf->getExtremePoints())[0] - 
			(general_center_X))*scale)+(general_center_X);
		(to_transf->getExtremePoints())[1] = (((to_transf->getExtremePoints())[1] - 
			(general_center_Y))*scale)+(general_center_Y);
		(to_transf->getExtremePoints())[2] = (((to_transf->getExtremePoints())[2] - 
			(general_center_X))*scale)+(general_center_X);
		(to_transf->getExtremePoints())[3] = (((to_transf->getExtremePoints())[3] - 
			(general_center_Y))*scale)+(general_center_Y);

		//calls the function to recalculate the center
		to_transf->recalculateCenter();
    }
}

/*
 * Method Overview: Rotates the lines by an specific amount
 * Parameters: Rotation degree (in radians)
 * Return: None
 */
void rotate(long double degree)
{
	long double pi = PI/180.0;
	long double rad = degree*pi;

	int i, j;

	long double general_center_X = 0.0;
	long double general_center_Y = 0.0;

	long double rotated_values[2];

	//calculates the general center of a group of lines
	for (i = 0; i < (int)selected_lines_id.size(); i++) 
	{
		general_center_X += (lines.find(selected_lines_id.at(i))->second)->getAnnotationCenter()[0];
		general_center_Y += (lines.find(selected_lines_id.at(i))->second)->getAnnotationCenter()[1];
	}

	//gets the average value
	general_center_X = general_center_X/(long double)selected_lines_id.size();
	general_center_Y = general_center_Y/(long double)selected_lines_id.size();

	//Loop through all the lines
	for (i = 0; i < (int)selected_lines_id.size(); i++) 
	{
		LineAnnotation* to_transf = lines.find(selected_lines_id.at(i))->second;

		for (j = 0; j < (int)((to_transf)->getPoints())->size(); j = j+2) 
        {
			//calls the rotete point function
			pointRotation(((to_transf)->getPoints())->at(j), ((to_transf)->getPoints())->at(j+1), 
				0, 0, rad, general_center_X, general_center_Y,rotated_values);

			//assigns the results
			((to_transf)->getPoints())->at(j) = rotated_values[0];
			((to_transf)->getPoints())->at(j+1) = rotated_values[1];
			
        }
		//calls the rotate point function
		pointRotation((to_transf->getExtremePoints())[0], (to_transf->getExtremePoints())[1], 
				0, 0, rad, general_center_X, general_center_Y, rotated_values);

		//assigns the results
		(to_transf->getExtremePoints())[0] = rotated_values[0];
		(to_transf->getExtremePoints())[1] = rotated_values[1];

		//calls the rotate point function
		pointRotation((to_transf->getExtremePoints())[2], (to_transf->getExtremePoints())[3], 
				0, 0, rad, general_center_X, general_center_Y, rotated_values);

		//assigns the results
		(to_transf->getExtremePoints())[2] = rotated_values[0];
		(to_transf->getExtremePoints())[3] = rotated_values[1];

		//calls the function to recalculate the center
		to_transf->recalculateCenter();
    }
}

/*
 * Method Overview: Rotates an specific point
 * Parameters (1): Point to rotate, distance to the center
 * Parameters (2): Angle to rotate, point to rotate around off
 * Parameters (3): Array with the rotated values
 * Return: None
 */
void pointRotation(long double X, long double Y, long double transX,long double transY,
				   long double angle, long double origX, long double origY, long double* rotated_values)
{
	//Variables used during the process
	long double xtransf0, ytransf0, cosx0, senx0, cosy0, seny0;

	//Translates the point to the center of the scene
	xtransf0 = (X + transX) - (origX);
	ytransf0 = (Y + transY) - (origY);

	//Calculates trigonometric values of the point
	cosx0 = cos(angle)*xtransf0;
	senx0 = sin(angle)*xtransf0;
	cosy0 = cos(angle)*ytransf0;
	seny0 = sin(angle)*ytransf0;

	//Calculates the new point
	xtransf0 = ((cosx0) - (seny0));
	ytransf0 = ((senx0) + (cosy0));

	rotated_values[0] = (xtransf0)+(origX);
	rotated_values[1] = (ytransf0)+(origY);	
}

/*
 * Method Overview: Has the respective processes to draw each line
 * Parameters: None
 * Return: None
 */
void drawLines()
{
	int i;

	//[xin,yin,xfin,yfin] of the line to draw
	int numbers[4];

	//Iterator to go through the map
    std::map<int, LineAnnotation*>::iterator iter;
	
	//loops to get each line
    for (iter = lines.begin(); iter != lines.end(); iter++)
    {
		//gets the line to be drawn
		LineAnnotation* to_draw;
		to_draw = iter->second;

		//Whereas this line is currently being selected
		int to_draw_state = to_draw->getSelectedState();

		//loops through the line
		for (i = 0; i < (int)(to_draw->getPoints()->size())-2; i = i+2) 
		{
			//array with the mappings to apply to the line
			//{mirroring, change +/- sign x,change +/- sign y}
			int controls[3] = {0,0,0};

			//fills the [xin,yin,xfin,yfin] array
			numbers[0] = (int)round(to_draw->getPoints()->at(i));
			numbers[1] = (int)round(to_draw->getPoints()->at(i+1));
			numbers[2] = (int)round(to_draw->getPoints()->at(i+2));
			numbers[3] = (int)round(to_draw->getPoints()->at(i+3));

			//Liang-Barskey clipping algorithm evaluation
			if (my_clip_window->clip_line(&numbers[0], &numbers[1], &numbers[2], &numbers[3]))
			{
				//Stores the (xin,yin) for demapping later on
				int orgX = numbers[0];
				int orgY = numbers[1];

				//Identify the octant in which the line is
				MapManager->octants(numbers,controls);

				//Maps the point to the first 
				MapManager->mapping(numbers,controls);

				//Calls Bressenham line algorithm
				bressenham(numbers[0], numbers[1], numbers[2], numbers[3], orgX, orgY, controls, to_draw_state);
			}
		}
	}
}

/*
 * Method Overview: Keyboard events handling
 * Parameters: Pressed Key, (x,y) positions of the mouse in screen
 * Return: None
 */
void keyboard(unsigned char key, int x, int y)
{
	//analyzes which key was pressed
    switch (key)
    {
		//quit
		case 'q': case 'Q':
			glutLeaveMainLoop();
			exit(0);
			break;
	}
}

/*
 * Method Overview: Method used to remove the selected lines
 * Parameters: None
 * Return: None
 */
void eraseSelectedLines()
{
	cleanBuffer();
			
	int counter;

	//Loop through all the lines
	for (counter = 0; counter < (int)selected_lines_id.size(); counter++) 
	{
		lines.erase(selected_lines_id.at(counter));
	}

	//Gets the virtual annotation's selected IDs
	vector<int> selected = myCommander->getSelectedIDs();

	for(counter = 0; counter < (int)selected.size();counter++)
	{
		selected_lines_id.push_back(selected.at(counter));
	}

	vector<long double> null_long_vector;
	vector<double> null_double_vector;
	myJSON->createJSONable(NULL, DELETE_ANNOTATION_COMMAND, &null_long_vector, NULL, null_double_vector, selected_lines_id);

	selected_lines_id.clear();

	drawLines();
}

/*
 * Method Overview: Method used to remove the selected lines
 * Parameters: None
 * Return: None
 */
void deselectAllLines()
{
	int counter;

	for(counter = 0; counter<(int)(selected_lines_id.size());counter++)
	{
		(lines.find(selected_lines_id.at(counter))->second)->setSelectedState(0);
	}

	selected_lines_id.clear();

	myCommander->setLineSelectedFlag(0);

	drawLines();
}

/*
 * Method Overview: Method used to remove all the lines
 * Parameters: None
 * Return: None
 */
void clearAllLines()
{
	cleanBuffer();

	selected_lines_id.clear();
			
	//Iterator to go through the map
    std::map<int, LineAnnotation*>::iterator iter;
	
	//Loops through all the lines
    for (iter = lines.begin(); iter != lines.end(); iter++)
    {
		selected_lines_id.push_back(iter->second->getID());
    }

	eraseSelectedLines();
}

/*
 * Method Overview: Kills the thread
 * Parameters: None
 * Return: None
 */
void endOpenGLContext()
{
	glutLeaveMainLoop();
	exit(0);
}

/*
 * Method Overview: Checks and interprets a command (if any)
 * Parameters: None
 * Return: None
 */
void checkAndInterpretCommand()
{
	if(myCommander->getAnnotationCommandFlag())
	{
		switch (myCommander->getAnnotationCommand())
		{	
			case DESELECT_ALL_LINES:
				deselectAllLines();
				break;

			case CLEAR_ALL_LINES:
				clearAllLines();
				break;

			case ERASE_LINES:
				eraseSelectedLines();
				break;

			case END_OPENGL_CONTEXT:
				endOpenGLContext();
				break;
		}
		myCommander->setAnnotationCommandFlag(0);
	}
}

/*
 * Method Overview: Uses the JSONManager to create a JSON Message
 * Parameters: Message command, annotation to make the massage from
 * Return: None
 */
void createJSONLineMessage(string command, LineAnnotation* annotation)
{
	vector<int> null_int_vector;
	vector<double> null_double_vector;
	myJSON->createJSONable(annotation->getID(), command, annotation->getPoints(), NULL, null_double_vector, null_int_vector);
}

/*
 * Method Overview: Starts the JSON Update process
 * Parameters: None
 * Return: None
 */
void startJSONLineUpdate()
{
	int i;

	//Loop through all the lines
	for (i = 0; i < (int)selected_lines_id.size(); i++) 
	{
		LineAnnotation* selected = lines.find(selected_lines_id.at(i))->second;

		createJSONLineMessage(UPDATE_ANNOTATION_COMMAND, selected);
	}
}

/*
 * Method Overview: Touch events handling
 * Parameters (1): Received action, line-to-work-on ID
 * Parameters (2): (x,y) positions of the event
 * Return: None
 */
void OpenGLtouchControls(int command, int id, long double x, long double y)
{
	//analyzes which event occured
    switch (command)
    {	
		//Rotations
		//rotate counterclockwise
		case ROTATE_CNTR_CLK:	
			cleanBuffer();
			rotate(2.0f);
			drawLines();
			break;

		//rotate clockwise
		case ROTATE_CLK:	
			cleanBuffer();
			rotate(-2.0f);
			drawLines();
			break;

		//Zooms
		//zoom in
		case ZOOM_IN:
			cleanBuffer();
			zoom(1.2f);
			drawLines();
			break;

		//zoom out
		case ZOOM_OUT:
			cleanBuffer();
			zoom(0.8f);
			drawLines();
			break;

		//Pans
		//right pan
		case TRANSLATE_RIGHT:
			cleanBuffer();
			translate(resolutionX/50.0f,0);
			drawLines();
			break;

		//left pan
		case TRANSLATE_LEFT:
			cleanBuffer();
			translate(-resolutionX/50.0f,0);
			drawLines();
			break;

		//up pan
		case TRANSLATE_UP:
			cleanBuffer();
			translate(0,resolutionY/50.0f);
			drawLines();
			break;

		//down pan
		case TRANSLATE_DOWN:
			cleanBuffer();
			translate(0,-resolutionY/50.0f);
			drawLines();
			break;

		//add a point to the line
		case ADD_POINT:
			addPoint(id,x,y);
			drawLines();
			lines.erase(id);
			break;

		//add line to line map
		case ADD_LINE:
			cleanBuffer();
			lines.insert(pair<int, LineAnnotation*>(id, temp_line));
			createJSONLineMessage(CREATE_ANNOTATION_COMMAND, temp_line);
			drawLines();
			break;

		//clear line to prevent wrong lines
		case CLEAR_LINE:
			if(temp_line!=NULL)
			{
				if((int)(temp_line->getPoints()->size())==2)
				{
					temp_line->getPoints()->clear();
					temp_line->setInitialExtremes();
				}
			}
			break;

		case ADD_POINT_ANNOTATION:
			{
				long double initial_point_distance = 5.0;
				long double angle;
				long double val = PI/180.0;
				long double rotated_values[2];

				int counter;

				//create enough points to make a round shape
				for(counter = 0; counter<=360;counter=counter+18)
				{
					//gets the new angle value
					angle = counter*val;

					//calls the rotete point function
					pointRotation(x, y, initial_point_distance, initial_point_distance, angle, x, y, rotated_values);

					//assigns the results
					addPoint(id,rotated_values[0],rotated_values[1]);
				}
				lines.insert(pair<int, LineAnnotation*>(id, temp_line));
				createJSONLineMessage(CREATE_ANNOTATION_COMMAND, temp_line);
				drawLines();
			}
			break;
	}

	//Redraw scene
	glutPostRedisplay();
}

/*
 * Method Overview: Sets an image as the scene background
 * Parameters: Image to draw in background
 * Return: None
 */
void setOpenCVImage(cv::Mat image)
{
	int i, j;

	//Loops through the scene
	for (i = 0; i < resolutionX; i++) 
	{
		for (j = 0; j < resolutionY; j++) 
		{
			//Retreives a single pixel from the image
			cv::Vec3b vector = image.at<cv::Vec3b>(j,i);

			//Calculates its RGB 0-1 equivalent from 0-255
			double atr = vector[0]/255.0;
			double atg = vector[1]/255.0;
			double atb = vector[2]/255.0;

			//Assings the color to the framebuffer in that position
			int annotation_green = (buffer[i][j].g != ANNOTATION_GREEN && buffer[i][j].g != ANNOTATION_BLUE);
			if(buffer[i][j].r != ANNOTATION_RED || annotation_green || buffer[i][j].b != ANNOTATION_BLUE)
			{
				buffer[i][j].b = atr;
				buffer[i][j].g = atg;
				buffer[i][j].r = atb;
			}
		}
	}
	//Redraw the lines in the scene
	drawLines();
}

/*
 * Method Overview: Creates a char* of the most recently added line
 * Parameters: line-to-return ID
 * Return: Char* with all the points of the line
 */
char* OpenGLgetNewLine(int id)
{
	string message;

	unsigned int counter;

	//for each parameter of the touch gesture
	for(counter = 0; counter<(lines.find(id)->second)->getPoints()->size();)
	{
		//converts double long value to int, then to string
		ostringstream param;
		param << (int)((lines.find(id)->second)->getPoints()->at(counter));
		message+=param.str();

		if(counter!=((lines.find(id)->second)->getPoints()->size()-1))
		{
			//add a / to the string
			message+="/";
		}

		counter++;
	}

	//create a char* from the created string
	char* writable = new char[message.size()+1];
	copy(message.begin(),message.end(),writable);
	writable[message.size()] = '\0';

	//return char*
	return writable;
}

/*
 * Method Overview: Point-in-polygon Algorithm Variant (see theory)
 * Parameters: Region of interest polygon
 * Return: None
 */
int pointInPolygon(vector<long double> roi_extremes)
{
	int selected = 0;

	int counter;
	for(counter = 0; counter<(int)(selected_lines_id.size());counter++)
	{
		(lines.find(selected_lines_id.at(counter))->second)->setSelectedState(0);
	}

	selected_lines_id.clear();

	int i; 

	//Iterator to go through the map
    std::map<int, LineAnnotation*>::iterator iter;
	
	//Loops through all the lines
    for (iter = lines.begin(); iter != lines.end(); iter++)
    {
		int crosses = 0;
		int wasException[1];
		wasException[0] = 0;

		long double* center = iter->second->getAnnotationCenter();

		for(i=0;i < (int)roi_extremes.size()-2; i=i+2)
		{
			//Yin-Yfin changes because of OpenGL Y axis orintation
			if(crossingLine((roi_extremes.at(i))-center[0],(abs(roi_extremes.at(i+3)-resolutionY))-center[1],
				(roi_extremes.at(i+2))-center[0],(abs(roi_extremes.at(i+1)-resolutionY))-center[1], wasException))
				crosses = !crosses;
		}
		if(crosses)
		{
			selected_lines_id.push_back(iter->second->getID());
			iter->second->setSelectedState(1);
		}
    }

	if((int)selected_lines_id.size()>0)
	{
		//Redraw the lines
		drawLines();

		//Redraw the scene
		glutPostRedisplay();

		selected = 1;
	}

	return selected;
}

/*
 * Method Overview: OpenGL pixel coloring for framebuffer positions
 * Parameters: None
 * Return: None
 */
void draw_scene()
{
	checkAndInterpretCommand();

	glClear(GL_COLOR_BUFFER_BIT);

	static int last_x = 0;
	int i, j;

	//Loops through the image
	for (i = 0; i < last_x; i++) 
	{
		for (j = 0; j < resolutionY; j++) 
		{
			//Creates an OpenGL color from the framebuffer color
			glColor3f((GLfloat)buffer[i][j].r,(GLfloat)buffer[i][j].g,(GLfloat)buffer[i][j].b);

			//Create a point in the scene of that specific color
	        glBegin(GL_POINTS);
	        glVertex2i(i,j);
	        glEnd();
		}
	}
	
	//Loops through the image
	for (i = last_x; i < resolutionX; i++) 
	{
		for (j = 0; j < resolutionY; j++) 
		{
			//Assign white color
			buffer[i][j].r = 1.0;
			buffer[i][j].g = 1.0;
			buffer[i][j].b = 1.0;

			//Creates an OpenGL color from the framebuffer color
			glColor3f((GLfloat)buffer[i][j].r,(GLfloat)buffer[i][j].g,(GLfloat)buffer[i][j].b);

			//Create a point in the scene of that specific color
			glBegin(GL_POINTS);
			glVertex2i(i,j);
			glEnd();
			last_x = i;
		}
	}

	glFlush();
}

/*
 * Method Overview: Refresh the scene when idle
 * Parameters: None
 * Return: None
 */
void refresh()
{
	//Redraw scene
	glutPostRedisplay();
}

/*
 * Method Overview: Creates the OpenGL scene and context
 * Parameters (1): Main values, scene-to-create resolution
 * Parameters (2): Instance of the Command Center
 * Parameters (3): Instance of the JSON Manager
 * Return: None
 */
void initWindow(int argc, char* argv[], int resX, int resY, CommandCenter* pCommander, JSONManager* pJSON)
{
	//Sets the CommandCenter instance as own
	myCommander = pCommander;

	//Sets the JSONManager instance as own
	myJSON = pJSON;

	//Assigns the scene resolution
	resolutionX = resX;
	resolutionY = resY;

	int i, j;

	//Allocates memory for the framebuffer
	buffer = (COLOR **)malloc(resolutionX * sizeof(COLOR*));
	for (i = 0; i < resolutionX; i++) 
	{
		buffer[i] = (COLOR *)malloc(resolutionY * sizeof(COLOR));
	}

	//Loops through the image
	for (i = 0; i < resolutionX; i++) 
	{
		for (j = 0; j < resolutionY; j++) 
		{
			//White initial background
			buffer[i][j].r = 1.0;
            buffer[i][j].g = 1.0;
            buffer[i][j].b = 1.0;
		}
	}

	//Coordinates of the clipping window
	my_clip_window = new LiangBarsky(0, 0, resolutionX-1, resolutionY-1);

	//In charge of perform octant mappings
	MapManager = new Mapping();

	//OpenGL Context and Functions initialization
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(resolutionX,resolutionY);
	glutCreateWindow("STAR Mentor System");
	glutFullScreen();
	glutIdleFunc(refresh);
	glutDisplayFunc(draw_scene);
	glutKeyboardFunc(keyboard);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	gluOrtho2D(-0.5, resolutionX +0.5, -0.5, resolutionY + 0.5);
	glutMainLoop();
}
