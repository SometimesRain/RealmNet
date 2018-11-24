#pragma once

#include <DataStructures/ConditionEffectData.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API ProjectileData //TODO add id
{
public:
	byte id;

	short damage;
	short lifetime;
	float speed;

	short maxDamage;
	short minDamage;

	float amplitude;
	float frequency;
	float magnitude;

	bool multiHit;
	bool passesCover;
	bool armorPierce;

	bool boomerang;
	bool parametric;
	bool wavy;

	short effectsAmount;
	ConditionEffectData* effects;
};