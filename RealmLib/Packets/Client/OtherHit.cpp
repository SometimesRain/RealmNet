#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "Packets/PacketWriter.h"
#include "Packets/PacketReader.h"

#include <Packets/OtherHit.h>

OtherHit::OtherHit(int time, byte bulletId, int objectId, int targetId)
	: time(time), bulletId(bulletId), objectId(objectId), targetId(targetId)
{

}

OtherHit::OtherHit(byte* data)
{
	PacketReader r(data);

	r.read(time);
	r.read(bulletId);
	r.read(objectId);
	r.read(targetId);
}

void OtherHit::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::OtherHit]);

	w.write(time);
	w.write(bulletId);
	w.write(objectId);
	w.write(targetId);
}

int OtherHit::size() const
{
	return 18;
}

String OtherHit::toString() const
{
	return String("OTHERHIT");
}