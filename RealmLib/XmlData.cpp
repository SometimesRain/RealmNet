#include "stdafx.h"

#include <GameData/XmlData.h>

std::map<int, ItemData*> typeToItem_;
std::map<int, ObjectData*> typeToObject_;
std::map<int, CharacterData*> typeToCharacter_;
std::map<ushort, TileData*> typeToTile_;

char* stringPool;
ConditionEffectData* effects;
ProjectileData* projectiles;
TileData* tiles;
ItemData* items;
CharacterData* characters;

ItemData* XmlData::typeToItem(int type)
{
	auto it = typeToItem_.find(type);
	if (it != typeToItem_.end())
		return it->second;
	return nullptr;
}

ObjectData* XmlData::typeToObject(int type)
{
	auto it = typeToObject_.find(type);
	if (it != typeToObject_.end())
		return it->second;
	return nullptr;
}

CharacterData* XmlData::typeToCharacter(int type)
{
	auto it = typeToCharacter_.find(type);
	if (it != typeToCharacter_.end())
		return it->second;
	return nullptr;
}

TileData* XmlData::typeToTile(ushort type)
{
	auto it = typeToTile_.find(type);
	if (it != typeToTile_.end())
		return it->second;
	return nullptr;
}

void XmlData::loadData()
{
	int temp;
	std::fstream bin("data.bin", std::ios::in | std::ios::binary);
	if (!bin.good())
	{
		printf("data.bin not found\n");
		return;
	}
	bin.read((char*)&temp, 4);
	printf("Loaded %d string characters\n", temp);
	stringPool = new char[temp];
	bin.read(stringPool, temp);

	bin.read((char*)&temp, 4);
	printf("Loaded %d effects\n", temp);
	effects = new ConditionEffectData[temp];
	bin.read((char*)effects, temp * sizeof(ConditionEffectData));

	bin.read((char*)&temp, 4);
	printf("Loaded %d projectiles\n", temp);
	projectiles = new ProjectileData[temp];
	bin.read((char*)projectiles, temp * sizeof(ProjectileData));

	for (int i = 0; i < temp; i++) //fix pointers
		projectiles[i].effects = effects + (int)projectiles[i].effects;

	bin.read((char*)&temp, 4);
	printf("Loaded %d tiles\n", temp);
	tiles = new TileData[temp];
	bin.read((char*)tiles, temp * sizeof(TileData));

	for (int i = 0; i < temp; i++) //fix pointers
	{
		tiles[i].name = stringPool + (int)tiles[i].name;
		typeToTile_[tiles[i].type] = tiles + i; //populate item map
	}

	bin.read((char*)&temp, 4);
	printf("Loaded %d items\n", temp);
	items = new ItemData[temp];
	bin.read((char*)items, temp * sizeof(ItemData));

	for (int i = 0; i < temp; i++) //fix pointers
	{
		items[i].name = stringPool + (int)items[i].name;
		items[i].projectiles = projectiles + (int)items[i].projectiles;
		typeToItem_[items[i].type] = items + i; //populate item map
	}

	bin.read((char*)&temp, 4);
	printf("Loaded %d characters\n", temp);
	characters = new CharacterData[temp];
	bin.read((char*)characters, temp * sizeof(CharacterData));

	for (int i = 0; i < temp; i++) //fix pointers
	{
		characters[i].name = stringPool + (int)characters[i].name;
		characters[i].projectiles = projectiles + (int)characters[i].projectiles;
		typeToObject_[characters[i].type] = characters + i; //populate object map
		typeToCharacter_[characters[i].type] = characters + i; //populate object map
	}

	bin.close();
}