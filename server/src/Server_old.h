//
//  Server.h
//  Asteroids-Server
//
//  Created by Travis True on 4/15/12.
//  Copyright (c) 2012 TRUESoft Entertainment. All rights reserved.
//

#ifndef SERVER_H
#define SERVER_H

#include "Connection.h"

#include <iostream>
#include <pthread.h>

#define SERVER_MAXHOSTNAME		256		// host name buffer size
#define SERVER_BACKLOG			10		// how many pending connections queue will hold
#define SERVER_PORT				1777	// the port users will be connecting to


using namespace CatalystEngine;


void *NetworkThread(void *ptr);


class Server
{
	friend void *NetworkThread(void *ptr);
	
protected:
	bool runCommandThread;
	bool runNetworkThread;
	int listenSocket;
	int highestSocket;
	fd_set socketSet;
	sockaddr_in serverInfo;
	pthread_t networkID;
	CatalystEngine::Collection *connections;
	
	void Initialize();
	void StartServer();
	void StopServer();
	void StartListener();
	void StopListener();
	
	void SetNonBlocking(int socket);
	void BuildSelectList();
	
	void AcceptConnection();
	void CloseConnection();
	
public:
	Server();
	~Server();
	
	void Process();
	
	bool IsCommandRunning();
	bool IsNetworkRunning();
	int GetListener();
	int GetHighestSocket();
	Connection *GetConnection(int index);
};

#endif // SERVER_H
