#include "stdafx.h"

#include <GameData/TypeManager.h>
#include <fstream>

byte TypeManager::typeToId[PacketType::NUM_PACKETS];
byte TypeManager::idToType[256];

void TypeManager::mapPackets()
{
	std::ifstream packets(".\\packets.bin", std::ios::binary);
	if (!packets.good())
	{
		printf("packets.bin not found\n");
		return;
	}
	std::copy(std::istreambuf_iterator<char>(packets), std::istreambuf_iterator<char>(), typeToId);

	memset(idToType, PacketType::NUM_PACKETS, 256);
	for (byte i = 0; i < PacketType::NUM_PACKETS; i++)
		idToType[typeToId[i]] = i;
}