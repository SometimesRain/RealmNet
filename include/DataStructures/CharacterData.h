#pragma once

#include <DataStructures/ObjectData.h>
#include <DataStructures/ProjectileData.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API CharacterData : public ObjectData
{
public:
	int maxHp;
	short defense;
	bool enemy;

	byte projectilesAmount;
	ProjectileData* projectiles;

	ProjectileData* getProjectile(byte bulletId);
};