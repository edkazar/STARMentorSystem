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
 * Name: communicationDefinitions.h
 *
 * Overview: Interface that contains the required definitions to
 * control the different types of servers that the Mentor System
 * has to receive and send different type of data through different
 * sockets.
 */
///////////////////////////////////////////////////////////////////

//Define guards
#ifndef COMMUNICATION_DEFINITIONS_H
#define COMMUNICATION_DEFINITIONS_H

//----------------------General Definitions----------------------//
//Max size of the created buffer
#ifndef MAX_PACKET_SIZE
#define MAX_PACKET_SIZE 1000000
#endif

//------------------------Port Definitions-----------------------//
//Port used for the video communication
#ifndef VIDEO_PORT
#define VIDEO_PORT "8989"
#endif

//Port used for the json communication
#ifndef JSON_PORT
#define JSON_PORT "8988"
#endif

//Port used for the gesture communication
#ifndef GESTURE_PORT
#define GESTURE_PORT "8987"
#endif

//-------------------------Network Types-------------------------//
//Code of the video network
#ifndef VIDEO_NETWORK_CODE
#define VIDEO_NETWORK_CODE 1
#endif

//Code of the json network
#ifndef JSON_NETWORK_CODE
#define JSON_NETWORK_CODE 2
#endif

//Code of the gesture network
#ifndef GESTURE_NETWORK_CODE
#define GESTURE_NETWORK_CODE 3
#endif

#endif