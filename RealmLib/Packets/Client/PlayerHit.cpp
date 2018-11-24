#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "Packets/PacketWriter.h"
#include "Packets/PacketReader.h"

#include <Packets/PlayerHit.h>

PlayerHit::PlayerHit(byte bulletId, int objectId)
	: bulletId(bulletId), objectId(objectId)
{

}

PlayerHit::PlayerHit(byte* data)
{
	PacketReader r(data);

	r.read(bulletId);
	r.read(objectId);
}

void PlayerHit::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::PlayerHit]);

	w.write(bulletId);
	w.write(objectId);
}

int PlayerHit::size() const
{
	return 10;
}

String PlayerHit::toString() const
{
	return String("PLAYERHIT");
}