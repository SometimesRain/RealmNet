#pragma once

#include <DataObjects/String.h>

class ServerSelection
{
public:
	String defaultHost; //ip of the currently selected game server (e.g. EUN2)
	String currentHost; //ip of the current world instance (e.g. nexus or a realm)

	ServerSelection(const char* server);
};