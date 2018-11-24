#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "Packets/PacketWriter.h"
#include "Packets/PacketReader.h"

#include <Packets/ShootAck.h>

ShootAck::ShootAck(int time)
	: time(time)
{

}

ShootAck::ShootAck(byte* data)
{
	PacketReader r(data);

	r.read(time);
}

void ShootAck::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::ShootAck]);

	w.write(time);
}

int ShootAck::size() const
{
	return 9;
}

String ShootAck::toString() const
{
	return String("SHOOTACK");
}