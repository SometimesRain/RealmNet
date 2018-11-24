#pragma once

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API ObjectData //inherit to CharacterData, GameObjectData, WallData
{
public:
	byte dataClass;
	ushort type;
	const char* name;
};