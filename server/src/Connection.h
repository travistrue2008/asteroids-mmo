//
//  Connection.h
//  Asteroids-Server
//
//  Created by Travis True on 4/12/12.
//  Copyright (c) 2012 TRUESoft Entertainment. All rights reserved.
//

#ifndef CONNECTION_H
#define CONNECTION_H

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>

#include "Message.h"
#include "Collection.h"


using namespace CatalystEngine;


struct ClientData
{
	short kills;
	float curShield;
	float maxShield;
};


class Connection : public CollectionItem
{
	friend class Server;
	
protected:
	int socket;
	bool accepted;
	sockaddr_in address;
	socklen_t addrLength;
	ClientData clientData;
	
	void Initialize();
	
public:
	Connection();
	Connection(int socket, struct sockaddr_in address, socklen_t addrLength);
	~Connection();
	
	int SendMessage(void *message, int size);
	
	bool IsAccepted();
	int GetSocket();
	char *GetAddress();
	sockaddr_in GetAddressInfo();
};


#endif // CONNECTION_H
