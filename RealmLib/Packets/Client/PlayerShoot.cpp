#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "Packets/PacketWriter.h"
#include "Packets/PacketReader.h"

#include <Packets/PlayerShoot.h>
#include <algorithm>

PlayerShoot::PlayerShoot(int time, byte bulletId, short itemType, const Location& position, float angle)
	: time(time), bulletId(bulletId), itemType(itemType), position(position), angle(angle)
{

}

PlayerShoot::PlayerShoot(byte* data)
{
	PacketReader r(data);

	r.read(time);
	r.read(bulletId);
	r.read(itemType);
	r.read(position);
	r.read(angle);
}

void PlayerShoot::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::PlayerShoot]);

	w.write(time);
	w.write(bulletId);
	w.write(itemType);
	w.write(position);
	w.write(angle);
}

int PlayerShoot::size() const
{
	return 24;
}

String PlayerShoot::toString() const
{
	return String("PLAYERSHOOT");
}