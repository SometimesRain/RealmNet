#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "Packets/PacketWriter.h"
#include "Packets/PacketReader.h"

#include <Packets/ServerPlayerShoot.h>

ServerPlayerShoot::ServerPlayerShoot(byte bulletId, int ownerId, int item, const Location& startPos, float angle, short damage)
	: bulletId(bulletId), ownerId(ownerId), item(item), startPos(startPos), angle(angle), damage(damage)
{

}

ServerPlayerShoot::ServerPlayerShoot(byte* data)
{
	PacketReader r(data);

	r.read(bulletId);
	r.read(ownerId);
	r.read(item);
	r.read(startPos);
	r.read(angle);
	r.read(damage);
}

void ServerPlayerShoot::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::ServerPlayerShoot]);

	w.write(bulletId);
	w.write(ownerId);
	w.write(item);
	w.write(startPos);
	w.write(angle);
	w.write(damage);
}

int ServerPlayerShoot::size() const
{
	return 28;
}

String ServerPlayerShoot::toString() const
{
	return String("SERVERPLAYERSHOOT");
}