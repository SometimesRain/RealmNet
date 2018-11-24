#pragma once

#include <DataObjects/String.h>
#include <DataObjects/Location.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API PlayerData
{
public:
	int objectId;
	int objectType; //class
	String name;
	Location position;
	int inventory[20];

	int maxHp;
	int hp;
	int maxMp;
	int mp;
	int attack;
	int defense;
	int speed;
	int dexterity;
	int wisdom;
	int vitality;

	int effects;
	int effects2;

	int oxygen;
	int sinkLevel;
};