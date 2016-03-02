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
 * Name: CommunicationManager.cpp
 *
 * Overview: .cpp of CommunicationManager.h
 */
///////////////////////////////////////////////////////////////////

//Include its header file
#include "CommunicationManager.h"

//---------------------------Variables---------------------------//
unsigned int CommunicationManager::video_client_id;
unsigned int CommunicationManager::json_client_id;
unsigned int CommunicationManager::gesture_client_id;

/*
 * Method Overview: Constructor of the class
 * Parameters: Port number
 * Return: Instance of the class
 */
CommunicationManager::CommunicationManager(void)
{
    //Id's to assign video clients for our table
    video_client_id = 0;

	//Id's to assign json clients for our table
    json_client_id = 0;

	//Id's to assign gesture clients for our table
    gesture_client_id = 0;

    //Set up the server network to listen 
    videoNetwork = new ServerNetwork(VIDEO_PORT);

	//Set up the server network to listen 
    jsonNetwork = new ServerNetwork(JSON_PORT);

	//Set up the server network to listen 
    gestureNetwork = new ServerNetwork(GESTURE_PORT);
}

/*
 * Method Overview: Destructor of the class
 * Parameters: None
 * Return: Cannot return
 */
CommunicationManager::~CommunicationManager(void)
{
}

/*
 * Method Overview: Calls the method to accept new clients
 * Parameters: None
 * Return: None
 */
void CommunicationManager::update()
{
	//If a new connection is accepted
	if(videoNetwork->acceptNewClient(video_client_id))
	{
		printf("video client %d has been connected to the server\n",video_client_id);

		//Increase the client counter
		video_client_id++;
	}
	if(jsonNetwork->acceptNewClient(json_client_id))
	{
		printf("json client %d has been connected to the server\n",json_client_id);

		//Increase the client counter
		json_client_id++;
	}
	if(gestureNetwork->acceptNewClient(gesture_client_id))
	{
		printf("gesture client %d has been connected to the server\n",gesture_client_id);

		//Increase the client counter
		json_client_id++;
	}
}

/*
 * Method Overview: Calls the method to receive data from clients
 * Parameters (1): Buffer and size of it to store the received data
 * Parameters (2): Type-of-client-to-send code
 * Return: Length of the received data
 */
int CommunicationManager::receiveFromClients(char * recvbuf, int bufSize, int networkType)
{
	int data_length = 0;

	if(networkType == VIDEO_NETWORK_CODE)
	{
		data_length = startReception(videoNetwork, recvbuf, bufSize);
	} 
	else if(networkType == GESTURE_NETWORK_CODE)
	{
		data_length = startReception(gestureNetwork, recvbuf, bufSize);
	}

	return data_length;
}

/*
 * Method Overview: Calls the method to send data to all clients
 * Parameters: Message to send, type-of-client-to-send code
 * Return: None
 */
int CommunicationManager::sendActionPackets(const char * message, int networkType)
{
    int iResult;

	if(networkType == JSON_NETWORK_CODE)
	{
		iResult = startDispatch(jsonNetwork, message);
	}

	return iResult;
}

/*
 * Method Overview: Calls the method to receive data from clients
 * Parameters (1): Network to use to receive data from
 * Parameters (2): Buffer to store the received data and its size
 * Return: Length of the received data
 */
int CommunicationManager::startReception(ServerNetwork* network, char * recvbuf, int bufSize)
{
	int data_length=0;
	int i;

	//Iterate until all the data from the socket is complete
	for(i = 0; i<bufSize;)
	{
		/*
			* Sometimes, the data to be received is too big to be
			* obtained in one iteration. This allows the socket to
			* keep track of where exactly in the data stream the 
			* buffer got fulled up so that, after its emptied, the
			* data reception can continue from that specific point
		*/
		data_length = network->receiveData(video_client_id-1, recvbuf+i, bufSize-i);


		//If there is data to receive
		if(data_length>=0)
		{
			//Update the data received counter with its lenght
			i += data_length;
		}
	}
	return data_length;
}

/*
 * Method Overview: Calls the method to send data to all clients
 * Parameters (1): Network to use to send data to
 * Parameters (2): Message to send, type-of-client-to-send code
 * Return: None
 */
int CommunicationManager::startDispatch(ServerNetwork* network, const char * message)
{
    int iResult;

	iResult = network->sendToAll(message);

	return iResult;
}