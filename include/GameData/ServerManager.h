#pragma once

#include <GameData/Constants.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

namespace ServerManager
{
	PACKET_API extern const char* idToAddr[Server::NUM_SERVERS];
	constexpr const char* idToAbbr[Server::NUM_SERVERS]
	{
		"use",
		"ase",
		"uss",
		"ussw",
		"use2",
		"usnw",
		"ae",
		"eusw",
		"uss2",
		"eun2",
		"eus",
		"uss3",
		"euw2",
		"usmw",
		"euw",
		"use3",
		"usw",
		"usw3",
		"usmw2",
		"eue",
		"aus",
		"eun",
		"usw2"
	};

	PACKET_API void loadServers();
}