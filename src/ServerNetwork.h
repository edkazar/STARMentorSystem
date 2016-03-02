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
 * Name: ServerNetwork.h
 *
 * Overview: This class serves as an interface between the
 * communication manager and the send/receive socket methods.
 * It is the one in charge of opening and creating the socket
 * for it to be used later on my the methods in NetworkServices.
 * This code was adapted from the one posted on CODEPROJECT by 
 * the user "bshokati" on Apr 22, 2013: 
 * http://www.codeproject.com/Articles/412511/Simple-client-server-network-using-Cplusplus-and-W
 */
///////////////////////////////////////////////////////////////////

//---------------------------Includes----------------------------//
#pragma once
#include <winsock2.h>//Windows Standard Socket Library
#include "NetworkServices.h"//Methods to communicate with clients
#include <ws2tcpip.h>//Windows TCP/IP Macros
#include <map>//Map Library

using namespace std;//Standard Libraries

//Enables the usage of the Winsocket Libraries
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

class ServerNetwork
{
public:
	//-------------------------Methods---------------------------//
	ServerNetwork(char* port_number);//Class Constructor
    ~ServerNetwork(void);//Class Destructor

	//Send data to all clients
    int sendToAll(const char * packets);
	
	//Receive incoming data
    int receiveData(unsigned int client_id, char * recvbuf, int bufSize);

	//Accept new connections
    bool acceptNewClient(unsigned int & id);


	//------------------------Variables--------------------------//
    //Socket to listen for new connections
    SOCKET ListenSocket;

    //Socket to give to the clients
    SOCKET ClientSocket;

    //For error checking return values
    int iResult;

    //Table to keep track of each client's socket
    std::map<unsigned int, SOCKET> sessions; 
};

