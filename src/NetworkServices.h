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
 * Name: NetworkServices.h
 *
 * Overview: The code has the Windows Socket methods used to 
 * exchange information with the clients. The class itself 
 * just have one method to send data and one to receive it.
 * This code was adapted from the one posted on CODEPROJECT by 
 * the user "bshokati" on Apr 22, 2013: 
 * http://www.codeproject.com/Articles/412511/Simple-client-server-network-using-Cplusplus-and-W
 */
///////////////////////////////////////////////////////////////////

//---------------------------Includes----------------------------//
#pragma once
#include <winsock2.h>//Windows Standard Socket Library

class NetworkServices
{
public:
	//-------------------------Methods---------------------------//
	//Send messages
	static int sendMessage(SOCKET curSocket, const char* message, int messageSize);

	//Receive message
	static int receiveMessage(SOCKET curSocket, char* buffer, int bufSize);

	//------------------------Variables--------------------------//
	//None
};

