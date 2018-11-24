#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"
#include "PacketReader.h"

#include <Packets/GotoAck.h>

GotoAck::GotoAck(int time)
	: time(time)
{

}

GotoAck::GotoAck(byte* data)
{
	PacketReader r(data);

	r.read(time);
}

void GotoAck::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::GotoAck]);

	w.write(time);
}

int GotoAck::size() const
{
	return 9;
}

String GotoAck::toString() const
{
	return String("GOTOACK");
}