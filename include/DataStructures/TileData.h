#pragma once

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API TileData
{
public:
	ushort type;
	const char* name;
	bool noWalk;
	float speed;
	bool sink;
	ushort minDamage;
	ushort maxDamage;
};