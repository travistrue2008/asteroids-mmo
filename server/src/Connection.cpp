//
//  Connection.cpp
//  Asteroids-Server
//
//  Created by Travis True on 4/12/12.
//  Copyright (c) 2012 TRUESoft Entertainment. All rights reserved.
//

#include "Connection.h"


Connection::Connection() : CollectionItem("", "player_connection")
{
	Initialize();
}


Connection::Connection(int socket, struct sockaddr_in address, socklen_t addrLength) : CollectionItem("", "player_connection")
{
	Initialize();
	this->socket = socket;
	this->address = address;
	this->addrLength = addrLength;
}


Connection::~Connection()
{

}


void Connection::Initialize()
{
	socket = 0;
	accepted = false;
	addrLength = 0;
	memset(&address, 0, sizeof(sockaddr_in));
	memset(&clientData, 0, sizeof(ClientData));
}


int Connection::SendMessage(void *message, int size)
{
	return send(socket, message, size, 0);
}


bool Connection::IsAccepted()
{ return accepted; }


int Connection::GetSocket()
{ return socket; }


char *Connection::GetAddress()
{ return inet_ntoa(address.sin_addr); }


sockaddr_in Connection::GetAddressInfo()
{ return address; }
