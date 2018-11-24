#include "stdafx.h"

#include <DataStructures/CharacterData.h>

ProjectileData* CharacterData::getProjectile(byte bulletId)
{
	for (byte i = 0; i < projectilesAmount; i++)
		if (projectiles[i].id == bulletId)
			return projectiles + i;
	return nullptr;
}