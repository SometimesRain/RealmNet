#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"
#include "PacketReader.h"

#include <Packets/AllyShoot.h>

AllyShoot::AllyShoot(byte bulletId, int ownerId, short itemType, float angle)
	: bulletId(bulletId), ownerId(ownerId), itemType(itemType), angle(angle)
{

}

AllyShoot::AllyShoot(byte* data)
{
	PacketReader r(data);

	r.read(bulletId);
	r.read(ownerId);
	r.read(itemType);
	r.read(angle);
}

void AllyShoot::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::AllyShoot]);

	w.write(bulletId);
	w.write(ownerId);
	w.write(itemType);
	w.write(angle);
}

int AllyShoot::size() const
{
	return 16;
}

String AllyShoot::toString() const
{
	return String("ALLYSHOOT");
}