//
//  Server.cpp
//  Asteroids-Server
//
//  Created by Travis True on 4/15/12.
//  Copyright (c) 2012 TRUESoft Entertainment. All rights reserved.
//

#include "Server.h"


pthread_mutex_t g_networkMutex = PTHREAD_MUTEX_INITIALIZER;


void *NetworkThread(void *ptr)
{
	int retVal = 0;
	int numConnections = 0;
	short messageType = 0;
	char buffer[MESSAGE_BUFFER_SIZE];
	struct timeval timeout;
	fd_set readSet;
	Connection *connection = NULL;
	
	// make sure the state and its parent are valid
	Server *server = (Server*)ptr;
	if(!server)
	{
		printf("FATAL ERROR: server unavailable\n");
		return NULL;
	}
	
	// set the timeout for 30 seconds and start listening
	timeout.tv_sec = 30;
	timeout.tv_usec = 0;
	
	// start listening
	pthread_mutex_lock(&g_networkMutex);
	server->StartListener();
	server->runNetworkThread = true;
	
	FD_ZERO(&server->socketSet);
	FD_ZERO(&readSet);
	FD_SET(server->GetListener(), &server->socketSet);
	server->highestSocket = server->GetListener();
	pthread_mutex_unlock(&g_networkMutex);
	
	// processing loop
	while(server->IsNetworkRunning())
	{
		// get information for select()
		pthread_mutex_lock(&g_networkMutex);
		//server->BuildSelectList();
		readSet = server->socketSet;
		//numConnections = server->GetHighestSocket() + 1;
		pthread_mutex_unlock(&g_networkMutex);
		
		// check for sockets ready to be read
		retVal = select(server->GetHighestSocket()+1, &readSet, NULL, NULL, &timeout);
		if(retVal < 0)
		{
			printf("FATAL ERROR: select() encountered an error (%i)\n", retVal);
			pthread_mutex_lock(&g_networkMutex);
			server->StopServer();
			pthread_mutex_unlock(&g_networkMutex);
			return NULL;
		}
		
		// explain a timeout
		if(!retVal)
		{
			//printf("select timed out, trying again\n");
			continue;
		}
		
		// process sockets
		pthread_mutex_lock(&g_networkMutex);
		for(int i=0;i<server->GetHighestSocket();i++)
		{
			// a valid socket was found
			if(FD_ISSET(i, &readSet))
			{
				printf("match found\n");
				// accept a new connection for listening
				if(server->GetListener() == i)
					server->AcceptConnection();
				else {
					// receive data from socket
					retVal = recv(i, buffer, MESSAGE_BUFFER_SIZE, 0);
					if(retVal < 1)
					{
						close(i);
						//FD_CLR(i, &server->socketSet);
						//readSet = server->socketSet;
						//printf("closing connection (%i)\n", retVal);
					} else {
						messageType = ((short)buffer[0] << 8) | (short)buffer[1];
						printf("%i: %s\n", messageType, buffer+2);
					}
				}
			}
		}
		pthread_mutex_unlock(&g_networkMutex);
	}
	
	// stop listening
	printf("network thread closed\n");
	pthread_mutex_lock(&g_networkMutex);
	server->StopListener();
	pthread_mutex_unlock(&g_networkMutex);
	return NULL;
}


Server::Server()
{
	Initialize();
	connections = new CatalystEngine::Collection("player_connection");
	
	// get the host name
	char hostName[SERVER_MAXHOSTNAME];
	gethostname(hostName, SERVER_MAXHOSTNAME);
	printf("Asteroid-MMO Server-1.0.1 on host: %s\n", hostName);
}


Server::~Server()
{
	// stop the server and free the mutex
	printf("~Server()");
	StopServer();
	pthread_mutex_destroy(&g_networkMutex);
	
	// release the player list
	if(connections)
	{
		delete connections;
		connections = NULL;
	}
	printf("server terminated\n");
}


void Server::Initialize()
{
	runCommandThread = true;
	runNetworkThread = false;
	listenSocket = 0;
	highestSocket = 0;
	
	networkID = NULL;
	connections = NULL;
	
	FD_ZERO(&socketSet);
	pthread_mutex_init(&g_networkMutex, NULL);
	
	// setup the address info
	memset(&serverInfo, 0, sizeof(sockaddr_in));
	serverInfo.sin_family = AF_INET;
	serverInfo.sin_addr.s_addr = htonl(INADDR_ANY); // Use any address available to the system
	serverInfo.sin_port = htons(SERVER_PORT);
}


void Server::StartServer()
{
	int retVal = 0;
	
	// create the network thread
	retVal = pthread_create(&networkID, NULL, NetworkThread, this);
	if(retVal != 0)
	{
		printf("FATAL ERROR: could not create network thread (%i)\n", retVal);
		return;
	}
}


void Server::StopServer()
{
	// clear the server flag
	pthread_mutex_lock(&g_networkMutex);
	runNetworkThread = false;
	pthread_mutex_unlock(&g_networkMutex);
	
	// halt execution until both threads have finished executing
	if(networkID)
	{
		printf("stopping server...\n");
		pthread_join(networkID, NULL);
		networkID = NULL;
	}
}


void Server::StartListener()
{
	int retVal = 0;
	int reuseAddr = 1;
	StopListener(); // stop the listener
	
	// create the listening socket
	listenSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(listenSocket < 0)
	{
		printf("ERROR: could not create listener socket (%i)\n", listenSocket);
		close(listenSocket);
		runNetworkThread = false;
	}
	
	// set socket options
	setsockopt(listenSocket, SOL_SOCKET, SO_REUSEADDR, &reuseAddr, sizeof(reuseAddr));
	//SetNonBlocking(listenSocket);
	
	// bind the socket to a port
	retVal = bind(listenSocket, (struct sockaddr*) &serverInfo, sizeof(sockaddr_in));
	if(retVal < 0)
	{
		printf("ERROR: could not bind listener socket (%i)\n", retVal);
		close(listenSocket);
		runNetworkThread = false;
	}
	
	// start listening and accept connections
	retVal = listen(listenSocket, SERVER_BACKLOG);
	if(retVal != 0)
	{
		printf("ERROR: listen() failed (%i)\n", retVal);
		close(listenSocket);
		runNetworkThread = false;
	} else printf("listening for incoming connections...\n");
}


void Server::StopListener()
{
	// close the listening socket if open
	if(listenSocket != 0)
	{
		close(listenSocket);
		listenSocket = 0;
	}
}


void Server::SetNonBlocking(int socket)
{
	int retVal = 0;
	int options = 0;
	
	// get options
	options = fcntl(socket, F_GETFL);
	if(options < 0)
	{
		printf("ERROR: could not get socket (%i) options (%i)\n", socket, options);
		return;
	}
	
	// set options
	options = (options | O_NONBLOCK);
	retVal = fcntl(socket, F_SETFL, options);
	if(retVal < 0)
	{
		printf("ERROR: could not set O_NONBLOCK for socket (%i)\n", socket);
		return;
	}
}


void Server::BuildSelectList()
{
	// clear the socket set and re-add the listener
	FD_ZERO(&socketSet);
	FD_SET(listenSocket, &socketSet);
	highestSocket = listenSocket; // set highest socket value to listener socket
	
	// add all sockets back into the list
	for(int i=0;i<connections->GetNumItems();i++)
	{
		Connection *connection = GetConnection(i);
		if(connection && connection->GetSocket() != 0)
		{
			FD_SET(connection->GetSocket(), &socketSet);
			if(highestSocket < connection->GetSocket())
				highestSocket = connection->GetSocket();
		}
	}
}


void Server::AcceptConnection()
{
	int numBytes = 0;
	int connectSocket = 0;
	sockaddr_in clientInfo;
	socklen_t clientLength;
	Connection *connection = NULL;
	
	// check for connections collection
	if(!connections)
	{
		printf("FATAL ERROR: connection list wasn't allocated\n");
		StopServer();
		runCommandThread = false;
		return;
	}
	
	// attempt to establish a connection
	connectSocket = accept(GetListener(), (struct sockaddr*)&clientInfo, &clientLength);
	if(connectSocket < 0)
		printf("refusing new connection\n");
	else {
		printf("new connection accepted from: %s\n", inet_ntoa(clientInfo.sin_addr));
		connection = new Connection(connectSocket, clientInfo, clientLength);
		//SetNonBlocking(connectSocket);
		connections->AddItem(connection);
	}
}


void Server::CloseConnection()
{

}


void Server::Process()
{
	char command[80];
	
	// process commands
	while(IsCommandRunning())
	{
		// grab input and lock mutex
		std::cin >> command;
		pthread_mutex_lock(&g_networkMutex);
		
		// start the server
		if(!strcmp(command, "start"))
		{
			// check if network thread is already running
			if(IsNetworkRunning())
				printf("ATTENTION: server already started\n");
			else
				StartServer();
			pthread_mutex_unlock(&g_networkMutex);
			continue;
		}
		
		// stop the server
		if(!strcmp(command, "stop"))
		{
			if(IsNetworkRunning())
				StopServer();
			else
				printf("ATTENTION: server isn't running\n");
			pthread_mutex_unlock(&g_networkMutex);
			continue;
		}
		
		// close the program
		if(!strcmp(command, "exit"))
		{
			printf("exiting...\n");
			StopServer();
			runCommandThread = false;
			pthread_mutex_unlock(&g_networkMutex);
			break;
		}
		
		// echo number of connections
		if(!strcmp(command, "show") && connections)
		{
			printf("number of connections: %i\n", connections->GetNumItems());
			for(int i=0;i<connections->GetNumItems();i++)
			{
				//printf("  %s\n", );
			}
			pthread_mutex_unlock(&g_networkMutex);
			continue;
		}
		
		// echo out unrecognized command
		printf("Syntax error: '%s' is not recognized command\n", command);
		pthread_mutex_unlock(&g_networkMutex);
	}
	printf("finished processing\n");
}


bool Server::IsCommandRunning()
{ return runCommandThread; }


bool Server::IsNetworkRunning()
{ return runNetworkThread; }


int Server::GetListener()
{ return listenSocket; }


int Server::GetHighestSocket()
{ return highestSocket; }


Connection *Server::GetConnection(int index)
{
	if(!connections) return NULL;
	return (Connection*)connections->GetItem(index);
}
