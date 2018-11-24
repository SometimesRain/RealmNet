#pragma once

#include <GameData/Constants.h>
#include <DataStructures/ItemData.h>
#include <DataStructures/ObjectData.h>
#include <DataStructures/TileData.h>
#include <DataStructures/CharacterData.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

namespace XmlData
{
	PACKET_API ItemData* typeToItem(int type);
	PACKET_API ObjectData* typeToObject(int type);
	PACKET_API CharacterData* typeToCharacter(int type);
	PACKET_API TileData* typeToTile(ushort type);

	PACKET_API void loadData();
}