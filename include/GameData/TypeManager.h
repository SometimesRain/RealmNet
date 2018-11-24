#pragma once

#include <GameData/Constants.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

namespace TypeManager
{
	PACKET_API extern byte typeToId[PacketType::NUM_PACKETS];
	PACKET_API extern byte idToType[256];

	PACKET_API void mapPackets();
}