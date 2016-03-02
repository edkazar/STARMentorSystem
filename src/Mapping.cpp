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
 * Name: Mapping.cpp
 *
 * Overview: .cpp of Mapping.h
 */
///////////////////////////////////////////////////////////////////

//Include its header file
#include "Mapping.h"

/*
 * Method Overview: Constructor of the class
 * Parameters: None
 * Return: Instance of the class
 */
Mapping::Mapping()
{
}

/*
 * Method Overview: Changes the color of a pixel in the framebuffer
 * Parameters (1): Array containing the line to draw
 * Parameters (2): Array with the flags to enable/disable
 * Return: None
 */
void Mapping::octants(int number[],int controls[])
{
	/*
	 * Control array composition:
	 * First argument: Whether or not to mirror the line completely
	 * Second argument: Whether or not to change the sign of the X
	 * Third argument: Whether or not to change the sign of the Y
	 */

	//octant identification
	if(number[2] > number[0])
	{
		if(number[3] > number[1])
		{
			//the line is in the second octant
			if(abs((number[2] - number[0])) <= abs((number[3] - number[1])))
			{
				controls[0] = 1;
				controls[1] = 1;
				controls[2] = 1;
			}
			//the line is in the first octant
			else
			{
				controls[0] = 0;
				controls[1] = 1;
				controls[2] = 1;
			}
		}

		else
		{
			//the line is in the seventh octant
			if(abs((number[2] - number[0])) <= abs((number[3] - number[1])))
			{
				controls[0] = 1;
				controls[1] = -1;
				controls[2] = 1;
			}
			//the line is in the eighth octant
			else
			{
				controls[0] = 0;
				controls[1] = 1;
				controls[2] = -1;
			}
		}
	}
	
	else
	{
		if(number[3] > number[1])
		{
			//the line is in the third octant
			if(abs((number[2] - number[0])) <= abs((number[3] - number[1])))
			{
				controls[0] = 1;
				controls[1] = 1;
				controls[2] = -1;
			}
			//the line is in the fourth octant
			else
			{
				controls[0] = 0;
				controls[1] = -1;
				controls[2] = 1;
			}
		}
		
		else
		{
			//the line is in the sixth octant
			if(abs((number[2] - number[0])) <= abs((number[3] - number[1])))
			{
				controls[0] = 1;
				controls[1] = -1;
				controls[2] = -1;
			}
			//the line is in the fifth octant
			else
			{
				controls[0] = 0;
				controls[1] = -1;
				controls[2] = -1;
			}
		}
	}
}

/*
 * Method Overview: Maps a line to its first octant equivalent
 * Parameters (1): Array containing the line to draw
 * Parameters (2): Array with the flags to perform the map
 * Return: None
 */
void Mapping::mapping(int number[],int controls[])
{
	int tempNum;

	//Coordenate axis translation
	if(number[0] > 0)
	{
		//Translate (Xfin,Yfin) by a (-Xin,-Yin) amount
		if(number[1] > 0)
		{
			number[2] = number[2] - abs(number[0]);
			number[3] = number[3] - abs(number[1]);
		}
		//Translate (Xfin,Yfin) by a (-Xin,Yin) amount
		else
		{
			number[2] = number[2] - abs(number[0]);
			number[3] = number[3] + abs(number[1]);
		}
	}

	else
	{
		//Translate (Xfin,Yfin) by a (Xin,-Yin) amount
		if(number[1] > 0)
		{
			number[2] = number[2] + abs(number[0]);
			number[3] = number[3] - abs(number[1]);
		}
		//Translate (Xfin,Yfin) by a (Xin,Yin) amount
		else
		{
			number[2] = number[2] + abs(number[0]);
			number[3] = number[3] + abs(number[1]);
		}
	}

	//The mapped line starts at the origin
	number[0] = 0;
	number[1] = 0;

	//Rotation to the first octant
	if(controls[0])
	{
		tempNum = number[2];
		number[2] = number[3];
		number[3] = tempNum;
	}

	//Change (or not) the sign of the number
	number[2] = number[2]*controls[1];
	number[3] = number[3]*controls[2];
}

/*
 * Method Overview: Demaps a mapped line to its respective octant
 * Parameters (1): Array containing the line to draw
 * Parameters (2): Array with the flags to perform the map
 * Parameters (3): Original (Xin,Yin) of the mapped line
 * Return: None
 */
void Mapping::demapping(int number[],int controls[],int orgX, int orgY)
{
	int tempNum;

	//Change (or not) the sign of the number
	number[0] = number[0]*controls[1];
	number[1] = number[1]*controls[2];

	//rotating towards the respective octants
	if(controls[0])
	{
		tempNum = number[0];
		number[0] = number[1];
		number[1] = tempNum;
	}

	//translating towards the respective octants
	if(orgX > 0)
	{
		//Translate (Xfin,Yfin) by a (Xin,Yin) amount
		if(orgY > 0)
		{
			number[0] = number[0] + abs(orgX);
			number[1] = number[1] + abs(orgY);
		}
		//Translate (Xfin,Yfin) by a (Xin,-Yin) amount
		else
		{
			number[0] = number[0] + abs(orgX);
			number[1] = number[1] - abs(orgY);
		}
	}

	else
	{
		//Translate (Xfin,Yfin) by a (-Xin,Yin) amount
		if(orgY > 0)
		{
			number[0] = number[0] - abs(orgX);
			number[1] = number[1] + abs(orgY);
		}
		//Translate (Xfin,Yfin) by a (-Xin,-Yin) amount
		else
		{
			number[0] = number[0] - abs(orgX);
			number[1] = number[1] - abs(orgY);
		}
	}
}
