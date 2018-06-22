//
//  Server_Receive.cpp
//  Asteroids-Server
//
//  Created by Travis True on 4/16/12.
//  Copyright (c) 2012 TRUESoft Entertainment. All rights reserved.
//

#include "Server.h"


void Server::ReceiveMessage(unsigned char *buffer, fd_set *masterSet, int size)
{
	// make sure the buffer is correct in size
	if(!buffer)
	{
		printf("Message::ReceiveData(): invalid buffer\n");
		return;
	}
	unsigned short messageType = ((unsigned short)buffer[1] << 8) | (unsigned short)buffer[0];
	unsigned short senderIndex = ((unsigned short)buffer[3] << 8) | (unsigned short)buffer[2];
	
	// convert the message type to the correct structure and process
	switch(messageType)
	{
		case MSG_NONE:
			// an error has occurred
			break;
			
		case MSG_CLIENT_CONNECT:
			ReceiveConnectMessage(buffer, masterSet);
			break;
			
		case MSG_CLIENT_DISCONNECT:
			ReceiveDisconnectMessage(buffer, masterSet);
			break;
			
		case MSG_ADD_PLAYER:
		case MSG_REMOVE_PLAYER:
		case MSG_INPUT:
		case MSG_COLLIDE:
		case MSG_SHOT:
		case MSG_DEATH:
		case MSG_KILLED:
		case MSG_RESPAWN:
			BroadcastMessage(senderIndex, buffer, size);
			break;
	}
}


void Server::BroadcastMessage(int senderIndex, void *buffer, int size)
{
	// boardcast message from sender to all other players
	for(int i=0;i<GetNumConnections();i++)
		if(i != senderIndex) GetConnection(i)->SendMessage(buffer, size);
}


void Server::ReceiveConnectMessage(unsigned char *buffer, fd_set *masterSet)
{
	Vector3 spawnPosition;
	ClientConnectMessage clientMessage;
	ServerConnectMessage serverMessage;
	AddPlayerMessage addMessage;
	
	// get client message info and setup server info
	memcpy(&clientMessage, buffer, sizeof(clientMessage));
	serverMessage.messageType = MSG_CLIENT_CONNECT;
	serverMessage.valid = 1;
	serverMessage.senderIndex = GetNumConnections() - 1;
	serverMessage.numPlayers = GetNumConnections();
	
	// set the server constants
	serverMessage.constants.respawnTime = 5.0f;
	serverMessage.constants.invincibleTime = 3.0f;
	serverMessage.constants.fieldSize = 4096.0f;
	
	// disconnect the player if version is incorrect (not up-to-date)
	if(strcmp(clientMessage.version, GetClientVersion()))
	{
		serverMessage.valid = 0;
		printf("version isn't correct, disconnecting from client\n");
		GetLastConnection()->SendMessage(&serverMessage, sizeof(serverMessage));
		RemoveConnection(serverMessage.senderIndex, masterSet);
		return;
	}
	
	// send user data to connection
	spawnPosition.x = (float)(rand() % 600) + 100.0f;
	spawnPosition.y = (float)(rand() % 400) + 100.0f;
	serverMessage.spawnPosition = spawnPosition;
	GetLastConnection()->accepted = true; // connection is accepted by server
	GetLastConnection()->SendMessage(&serverMessage, sizeof(serverMessage));
	
	// tell all other connections to add the new player
	for(int i=0;i<GetNumConnections()-1;i++)
	{
		addMessage.messageType = MSG_ADD_PLAYER;
		addMessage.spawnPosition = spawnPosition;
		GetConnection(i)->SendMessage(&addMessage, sizeof(addMessage));
	}
}


void Server::ReceiveDisconnectMessage(unsigned char *buffer, fd_set *masterSet)
{
	DisconnectMessage message;
	memcpy(&message, buffer, sizeof(message));
	RemoveConnection(message.senderIndex, masterSet);
}
