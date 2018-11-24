#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "Packets/PacketWriter.h"
#include "Packets/PacketReader.h"

#include <Packets/EnemyShoot.h>

EnemyShoot::EnemyShoot(byte bulletId, int ownerId, byte bulletType, const Location& position, float angle, short damage, byte numShots, float angleInc)
	: bulletId(bulletId), ownerId(ownerId), bulletType(bulletType), position(position), angle(angle), damage(damage), numShots(numShots), angleInc(angleInc)
{

}

EnemyShoot::EnemyShoot(byte* data)
{
	PacketReader r(data);

	r.read(bulletId);
	r.read(ownerId);
	r.read(bulletType);
	r.read(position);
	r.read(angle);
	r.read(damage);

	if (r.more())
	{
		r.read(numShots);
		r.read(angleInc);
	}
	else
	{
		numShots = 1;
		angleInc = 0;
	}
}

void EnemyShoot::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::EnemyShoot]);

	w.write(bulletId);
	w.write(ownerId);
	w.write(bulletType);
	w.write(position);
	w.write(angle);
	w.write(damage);

	if (numShots != 1)
	{
		w.write(numShots);
		w.write(angleInc);
	}
}

int EnemyShoot::size() const
{
	if (numShots == 1)
		return 25;
	else
		return 30;
}

String EnemyShoot::toString() const
{
	return String("ENEMYSHOOT");
}