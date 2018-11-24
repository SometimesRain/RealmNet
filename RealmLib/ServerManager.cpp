#include "stdafx.h"

#include <GameData/ServerManager.h>

const char* ServerManager::idToAddr[Server::NUM_SERVERS];

char* addresses;

void ServerManager::loadServers()
{
	int temp;
	std::fstream bin("servers.bin", std::ios::in | std::ios::binary);
	if (!bin.good())
	{
		printf("servers.bin not found\n");
		return;
	}
	bin.read((char*)&temp, 4);
	addresses = new char[temp];
	bin.read(addresses, temp);

	bin.read((char*)&temp, 4);
	printf("Loaded %d servers\n", temp);
	int* offsets = new int[temp];
	bin.read((char*)offsets, temp * sizeof(int));

	for (byte i = 0; i < Server::NUM_SERVERS; i++)
	{
		idToAddr[i] = addresses + offsets[i];
	}
}