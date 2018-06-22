//
//  Server.cpp
//  Asteroids-Server
//
//  Created by Travis True on 4/15/12.
//  Copyright (c) 2012 TRUESoft Entertainment. All rights reserved.
//

#include "Server.h"


pthread_mutex_t g_networkMutex = PTHREAD_MUTEX_INITIALIZER;


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
	maxPlayers = 0;
	numMessageSent = 0;
	numMessageReceived = 0;
	
	networkID = NULL;
	connections = NULL;
	
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
	runNetworkThread = true;
}


void Server::StopServer()
{	
	// halt execution until both threads have finished executing
	runNetworkThread = false;
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
	int optOn = 1;
	StopListener(); // stop the listener
	
	// create the listening socket
	listenSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(listenSocket < 0)
	{
		printf("ERROR: could not create listener socket (%i)\n", listenSocket);
		close(listenSocket);
		runNetworkThread = false;
	}
	
	// attempt to reuse address
	retVal = setsockopt(listenSocket, SOL_SOCKET, SO_REUSEADDR, &optOn, sizeof(optOn));
	if(retVal < 0) printf("WARNING: could not reuse address");
	
	// set the socket to non-blocking
	retVal = ioctl(listenSocket, FIONBIO, &optOn);
	if(retVal < 0)
	{
		printf("ERROR: could not set listener to non-blocking\n");
		close(listenSocket);
		runNetworkThread = false;
	}
	
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


void Server::AddConnection()
{
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
	do {
		connectSocket = accept(GetListener(), (struct sockaddr*)&clientInfo, &clientLength);
		if(connectSocket < 0)
		{
			//printf("no new connections left (%i)\n", connectSocket);
			break;
		} else {
			printf("new connection accepted from: %s\n", inet_ntoa(clientInfo.sin_addr));
			connection = new Connection(connectSocket, clientInfo, clientLength);
			connections->AddItem(connection);
			if(connections->GetNumItems() > maxPlayers)
				maxPlayers = connections->GetNumItems();
		}
	} while(1);
}


void Server::RemoveConnection(int index, fd_set *masterSet)
{
	Connection *connect = GetConnection(index);
	bool wasAccepted = connect->IsAccepted();
	FD_CLR(connect->GetSocket(), masterSet);
	close(connect->GetSocket());
	connections->RemoveItem(index);
	printf("disconnected from client\n");
	
	// tell all other connections to remove the connection
	if(wasAccepted)
		for(int i=0;i<GetNumConnections();i++)
		{
			RemovePlayerMessage message;
			message.messageType = MSG_REMOVE_PLAYER;
			message.senderIndex = index;
			message.updatedIndex = i;
			GetConnection(i)->SendMessage(&message, sizeof(message));
		}
}


void Server::Process()
{
	char command[80];
	
	// process commands
	while(IsCommandRunning())
	{
		// grab input and lock mutex
		std::cin >> command;
		
		// close the program
		if(!strcmp(command, "exit"))
		{
			printf("exiting...\n");
			StopServer();
			runCommandThread = false;
			break;
		}
		
		// start the server
		if(!strcmp(command, "start"))
		{
			// check if network thread is already running
			if(IsNetworkRunning())
				printf("ATTENTION: server already started\n");
			else
				StartServer();
			continue;
		}
		
		// stop the server
		if(!strcmp(command, "stop"))
		{
			if(IsNetworkRunning())
				StopServer();
			else
				printf("ATTENTION: server isn't running\n");
			continue;
		}
		
		// echo number of connections
		if(!strcmp(command, "show") && connections)
		{
			printf("number of connections: %i\n", connections->GetNumItems());
			for(int i=0;i<connections->GetNumItems();i++)
			{
				printf("  %s\n", GetConnection(i)->GetAddress());
			}
			continue;
		}
		
		// get the max amount of players playing the session at once
		if(!strcmp(command, "maxPlayers"))
		{
			printf("maxPlayers: %i\n", maxPlayers);
			continue;
		}
		
		// echo out unrecognized command
		printf("Syntax error: '%s' is not recognized command\n", command);
	}
}


bool Server::IsCommandRunning()
{ return runCommandThread; }


bool Server::IsNetworkRunning()
{ return runNetworkThread; }


int Server::GetListener()
{ return listenSocket; }


int Server::GetMaxPlayers()
{ return maxPlayers; }


int Server::GetNumConnections()
{
	if(!connections) return 0;
	return connections->GetNumItems();
}


Connection *Server::GetConnection(int index)
{
	if(!connections) return NULL;
	return (Connection*)connections->GetItem(index);
}


Connection *Server::GetLastConnection()
{
	if(!connections) return NULL;
	return GetConnection(connections->GetNumItems()-1);
}
