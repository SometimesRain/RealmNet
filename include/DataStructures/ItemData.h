#pragma once

#include <DataStructures/ProjectileData.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API ItemData
{
public:
	ushort type;
	const char* name;

	byte slotType;
	byte tier;
	byte bagType;
	byte numProjectiles;

	bool soulbound;
	bool consumable;
	short buffDuration;

	ushort manaCost;
	ushort cooldown;
	ushort feedPower;

	float fireRate;

	byte projectilesAmount;
	ProjectileData* projectiles;
};