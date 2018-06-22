//
//  Server_Thread.cpp
//  Asteroids-Server
//
//  Created by Travis True on 4/16/12.
//  Copyright (c) 2012 TRUESoft Entertainment. All rights reserved.
//

#include "Server.h"


void *NetworkThread(void *ptr)
{
	int retVal = 0;
	int fdMax = 0;
	int numBytes = 0;
	unsigned char buffer[MESSAGE_BUFFER_SIZE];
	struct timeval timeout;
	fd_set masterSet;
	fd_set readSet;
	
	// make sure the state and its parent are valid
	Server *server = (Server*)ptr;
	if(!server)
	{
		printf("FATAL ERROR: server unavailable\n");
		return NULL;
	}
	
	// set the timeout for 10 seconds and clear FD sets
	timeout.tv_sec = 1;
	timeout.tv_usec = 0;
	FD_ZERO(&masterSet);
	FD_ZERO(&readSet);
	
	// start listening
	server->StartListener();
	FD_SET(server->GetListener(), &masterSet);
	fdMax = server->GetListener();
	
	// processing loop
	while(server->IsNetworkRunning())
	{
		// check for sockets ready to be read
		memcpy(&readSet, &masterSet, sizeof(masterSet));
		retVal = select(fdMax+1, &readSet, NULL, NULL, &timeout);
		if(retVal < 0)
		{
			printf("FATAL ERROR: select() encountered an error (%i)\n", retVal);
			server->StopServer();
			return NULL;
		}
		
		// explain a timeout
		if(!retVal)
		{
			//printf("select timed out, trying again\n");
			continue;
		}
		
		// process the listening socket
		if(FD_ISSET(server->GetListener(), &readSet))
		{
			server->AddConnection();
			FD_SET(server->GetLastConnection()->GetSocket(), &masterSet);
			if(fdMax < server->GetLastConnection()->GetSocket())
				fdMax = server->GetLastConnection()->GetSocket();
		}
		
		// process other sockets
		for(int i=0;i<server->GetNumConnections();i++)
		{
			Connection *connect = server->GetConnection(i);
			if(FD_ISSET(connect->GetSocket(), &readSet))
			{
				// receive data from socket
				numBytes = recv(connect->GetSocket(), buffer, MESSAGE_BUFFER_SIZE, 0);
				if(numBytes < 1)
					server->RemoveConnection(i, &masterSet);
				else
					server->ReceiveMessage(buffer, &masterSet, numBytes);
			}
		}
	}
	
	// stop listening
	server->StopListener();
	printf("network thread closed\n");
	return NULL;
}
