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
 * Name: ServerNetwork.cpp
 *
 * Overview: .cpp of ServerNetwork.h
 */
///////////////////////////////////////////////////////////////////

//Include its header file
#include "ServerNetwork.h"

/*
 * Method Overview: Constructor of the class
 * Parameters: Port number
 * Return: Instance of the class
 */
ServerNetwork::ServerNetwork(char* port_number)
{
	// Create WSADATA object
    WSADATA wsaData;

    // Sockets for the server
    ListenSocket = INVALID_SOCKET;
    ClientSocket = INVALID_SOCKET;

    // Address info for the server to listen to
    struct addrinfo *result = NULL;
    struct addrinfo hints;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        exit(1);
    }

    // Set address information
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;//TCP connection
    hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
    iResult = getaddrinfo(NULL, port_number, &hints, &result);

    if ( iResult != 0 ) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        exit(1);
    }

    // Create a Socket for connecting to server
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        exit(1);
    }

    // Set the mode of the socket to be nonblocking
    u_long iMode = 1;
    iResult = ioctlsocket(ListenSocket, FIONBIO, &iMode);

    if (iResult == SOCKET_ERROR) {
        printf("ioctlsocket failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        exit(1);
    }

    // Setup the TCP listening socket
    iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);

    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        exit(1);
    }

    // No longer need address information
    freeaddrinfo(result);

    // Start listening for new clients attempting to connect
    iResult = listen(ListenSocket, SOMAXCONN);

    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        exit(1);
    }
}

/*
 * Method Overview: Destructor of the class
 * Parameters: None
 * Return: Cannot return
 */
ServerNetwork::~ServerNetwork(void)
{
}

/*
 * Method Overview: Method used to add new clients to client map
 * Parameters: Id of new client to add to map
 * Return: Bool to indicate if an addition was made
 */
bool ServerNetwork::acceptNewClient(unsigned int & id)
{
    // Accept the connection and save the socket
    ClientSocket = accept(ListenSocket,NULL,NULL);

    if (ClientSocket != INVALID_SOCKET) 
    {
        //dSisable nagle on the client's socket
        char value = 1;
        setsockopt( ClientSocket, IPPROTO_TCP, TCP_NODELAY, &value, sizeof( value ) );

        // Insert new client into session ID table
        sessions.insert( pair<unsigned int, SOCKET>(id, ClientSocket) );

        return true;
    }

    return false;
}

/*
 * Method Overview: Method to receive incoming data from a client
 * Parameters: Id of client from, buffer to store data and its size
 * Return: the number of bytes received
 */
int ServerNetwork::receiveData(unsigned int client_id, char * recvbuf, int bufSize)
{
	//If the client ID exists in the table
    if( sessions.find(client_id) != sessions.end() )
    {
		//get the socket in which the specific client if connected
        SOCKET currentSocket = sessions[client_id];
	
		//call NetworkServices to receive the message
        iResult = NetworkServices::receiveMessage(currentSocket, recvbuf, bufSize);

		//Close connection if client is no longer logged
        if (iResult == 0)
        {
            printf("Connection closed\n");
            closesocket(currentSocket);
        }

        return iResult;
    }

    return 0;
}


/*
 * Method Overview: Method to send a message to the logged clients
 * Parameters: Message to send to all the clients
 * Return: Result of the message
 */
int ServerNetwork::sendToAll(const char * message)
{
	//Socket to send the data
    SOCKET currentSocket;

	//Iterator to go through the map
    std::map<unsigned int, SOCKET>::iterator iter;

    int iSendResult;
	
	//Go through all the clients on the map
    for (iter = sessions.begin(); iter != sessions.end(); iter++)
    {
		//assign the correct socket to send to
        currentSocket = iter->second;

		//call NetworkServices to send the message
        iSendResult = NetworkServices::sendMessage(currentSocket, message, strlen(message));
    }
	
	return iSendResult;
}