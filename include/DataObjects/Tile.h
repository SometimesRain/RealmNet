#pragma once

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API Tile
{
public:
	short x;
	short y;
	ushort type;

	Tile(short x, short y, ushort type);
	Tile();
};