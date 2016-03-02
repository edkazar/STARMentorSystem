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
 * Name: CommunicationManager.h
 *
 * Overview: This class coordinates the processes related to the
 * connection of the Mentor System with the Trainee System. By
 * itself, contains a loop to accept new clients, but it also 
 * has the required methods to notify the other classes when
 * they need to send or receive data from the available clients.
 * This code was adapted from the one posted on CODEPROJECT by 
 * the user "bshokati" on Apr 22, 2013: 
 * http://www.codeproject.com/Articles/412511/Simple-client-server-network-using-Cplusplus-and-W
 */
///////////////////////////////////////////////////////////////////

#pragma once
//---------------------------Includes----------------------------//
#include "ServerNetwork.h"//Socket Handling
#include "communicationDefinitions.h"//Socket-related definitions

class CommunicationManager
{
public:
	//-------------------------Methods---------------------------//
	CommunicationManager(void);//Class Constructor
    ~CommunicationManager(void);//Class Destructor

	//Accept new Clients
    void update();

	//Notify Socket Handling Object to recieve a video message
	int receiveFromClients(char * recvbuf, int bufSize, int networkType);

	//Notify Socket Handling Object to send a message
	int sendActionPackets(const char * message, int networkType);

	//------------------------Variables--------------------------//
	//IDs for clients connecting to video clients table
	static unsigned int video_client_id;

	//IDs for clients connecting to json clients table
	static unsigned int json_client_id;

	//IDs for clients connecting to gesture clients table
	static unsigned int gesture_client_id;

private:
	//-------------------------Methods---------------------------//
	//Actually starts the reception of a message
	int startReception(ServerNetwork* network, char * recvbuf, int bufSize);

	//Actually starts the dispatch of a message
	int startDispatch(ServerNetwork* network, const char * message);

	//------------------------Variables--------------------------//
    //The video Socket Handling Object
    ServerNetwork* videoNetwork;

	//The json Socket Handling Object
    ServerNetwork* jsonNetwork;

	//The gesture Socket Handling Object
    ServerNetwork* gestureNetwork;

	//Data buffer to store the information sent through the socket
    char network_data[MAX_PACKET_SIZE];
};