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
 * Name: NetworkServices.cpp
 *
 * Overview: .cpp of NetworkServices.h
 */
///////////////////////////////////////////////////////////////////

//Include its header file
#include "NetworkServices.h"

/*
 * Method Overview: Sends a message through a specified socket
 * Parameters: Socket to send to, message to send and its size
 * Return: the number of bytes sent
 */
int NetworkServices::sendMessage(SOCKET curSocket, const char* message, int messageSize)
{
    return send(curSocket, message, messageSize, 0);
}

/*
 * Method Overview: Receives a message through a specified socket
 * Parameters: Socket to recieve from, buffer and size to store at 
 * Return: the number of bytes received
 */
int NetworkServices::receiveMessage(SOCKET curSocket, char* buffer, int bufSize)
{
    return recv(curSocket, buffer, bufSize, 0);
}