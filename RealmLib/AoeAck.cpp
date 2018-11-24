#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"
#include "PacketReader.h"

#include <Packets/AoeAck.h>

AoeAck::AoeAck(int time, const Location& position)
	: time(time), position(position)
{

}

AoeAck::AoeAck(int time, float x, float y)
	: time(time), position(x, y)
{

}

AoeAck::AoeAck(byte* data)
{
	PacketReader r(data);

	r.read(time);
	r.read(position);
}

void AoeAck::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::AoeAck]);

	w.write(time);
	w.write(position);
}

int AoeAck::size() const
{
	return 17;
}

String AoeAck::toString() const
{
	return String("AOEACK");
}