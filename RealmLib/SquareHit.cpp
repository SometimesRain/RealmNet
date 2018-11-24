#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"
#include "PacketReader.h"

#include <Packets/SquareHit.h>

SquareHit::SquareHit(int time, byte bulletId, int objectId)
	: time(time), bulletId(bulletId), objectId(objectId)
{

}

SquareHit::SquareHit(byte* data)
{
	PacketReader r(data);

	r.read(time);
	r.read(bulletId);
	r.read(objectId);
}

void SquareHit::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::SquareHit]);

	w.write(time);
	w.write(bulletId);
	w.write(objectId);
}

int SquareHit::size() const
{
	return 14;
}

String SquareHit::toString() const
{
	return String("SQUAREHIT");
}