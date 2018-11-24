#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"
#include "PacketReader.h"

#include <Packets/EnemyHit.h>

EnemyHit::EnemyHit(int time, byte bulletId, int targetId, bool kill)
	: time(time), bulletId(bulletId), targetId(targetId), kill(kill)
{

}

EnemyHit::EnemyHit(byte* data)
{
	PacketReader r(data);

	r.read(time);
	r.read(bulletId);
	r.read(targetId);
	r.read(kill);
}

void EnemyHit::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::EnemyHit]);

	w.write(time);
	w.write(bulletId);
	w.write(targetId);
	w.write(kill);
}

int EnemyHit::size() const
{
	return 15;
}

String EnemyHit::toString() const
{
	return String("ENEMYHIT");
}