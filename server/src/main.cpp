//
//  main.cpp
//  Asteroids-Server
//
//  Created by Travis True on 4/11/12.
//  Copyright (c) 2012 TRUESoft Entertainment. All rights reserved.
//


#include "Server.h"


using namespace CatalystEngine;


int main(int argc, const char * argv[])
{
	srand(NULL); // randomize the random variable
	Server *server = new Server();
	server->Process();
	delete server;
    return 0;
}
