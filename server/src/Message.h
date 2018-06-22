//
//  Message.h
//  Asteroids-Server
//
//  Created by Travis True on 4/15/12.
//  Copyright (c) 2012 TRUESoft Entertainment. All rights reserved.
//

#ifndef MESSAGE_H
#define MESSAGE_H

#include "Vector.h"

#define MESSAGE_BUFFER_SIZE 8192

// server messages
#define MSG_NONE						0			// default message type from server which suggests packet error
#define MSG_CLIENT_CONNECT				1			// send connecting data such as IP address, version, and device type
#define MSG_CLIENT_DISCONNECT			2			// player has disconnected from the game
#define MSG_ADD_PLAYER					3			// a new player has joined the game
#define MSG_REMOVE_PLAYER				4			// a player with index number left the game
#define MSG_INPUT						5			// a player with index has input data and position/direction available
#define MSG_COLLIDE						6			// player with index collided with another player
#define MSG_SHOT						7			// player with index was shot
#define MSG_DEATH						8			// player with index was destroyed, but not by another player
#define MSG_KILLED						9			// player with index was killed by another player with index
#define MSG_RESPAWN						10			// player with index respawned and is temporarily invincible

// platform types
#define PLATFORM_TYPE_WINDOWS			101			// Windows Vista and higher
#define PLATFORM_TYPE_LINUX				102			// Linux distro using GLUT
#define PLATFORM_TYPE_UNIX				103			// Unix distro using GLUT
#define PLATFORM_TYPE_MAC				104			// Mac Lion and higher
#define PLATFORM_TYPE_IPHONE			105			// iPhone 4 and higher
#define PLATFORM_TYPE_IPAD				106			// iPad


using namespace CatalystEngine;


const char *GetClientVersion();


struct ServerConstants
{
	float respawnTime;
	float invincibleTime;
	float fieldSize;
};


struct GenericMessage
{
	unsigned short messageType;						// message type
	unsigned short senderIndex;						// index of the player sending the message
};


typedef GenericMessage DisconnectMessage;			// message to disconnect a player
typedef GenericMessage DeathMessage;				// message to kill off a player


struct ServerConnectMessage
{
	unsigned short messageType;						// message type
	unsigned short senderIndex;						// index of the player sending the message
	
	unsigned short valid;							// whether the player's version and platform are supported
	unsigned short numPlayers;						// number of players in the game including this player if VALID=1
	Vector3 spawnPosition;							// player's spawn position
	ServerConstants constants;						// gameplay variables meant to alter gameplay without the need for updates
};


struct ClientConnectMessage
{
	unsigned short messageType;						// message type
	unsigned short senderIndex;						// index of the player sending the message
	
	char version[24];								// version string info
	unsigned short platform;						// platform code the user is connecting to the server on
};


struct AddPlayerMessage
{
	unsigned short messageType;						// message type
	unsigned short senderIndex;						// index of the player sending the message
	
	Vector3 spawnPosition;
};


struct RemovePlayerMessage
{
	unsigned short messageType;						// message type
	unsigned short senderIndex;						// index of the player sending the message
	
	unsigned short updatedIndex;					// player's updated index in the list
};


struct InputMessage
{
	unsigned short messageType;						// message type
	unsigned short senderIndex;						// index of the player sending the message
	
	short kills;									// current kills
	unsigned short input;							// current input selected to apply to player
	float curShield;								// current shield
	float maxShield;								// max shield
	float rotation;									// current rotation
	Vector3 position;								// current position
};


struct ShotMessage
{
	unsigned short messageType;						// message type
	unsigned short senderIndex;						// index of the player sending the message
	
	unsigned short shooterIndex;
};


struct CollideMessage
{
	unsigned short messageType;						// message type
	unsigned short senderIndex;						// index of the player sending the message
	
	unsigned short collideIndex;
};


struct KilledMessage
{
	unsigned short messageType;						// message type
	unsigned short senderIndex;						// index of the player sending the message
	
	int killerIndex;
};


struct RespawnMessage
{
	unsigned short messageType;						// message type
	unsigned short senderIndex;						// index of the player sending the message
	
	Vector3 spawnPosition;
};

#endif // MESSAGE_H
