#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"
#include "PacketReader.h"

#include <Packets/Ping.h>

Ping::Ping(int serial)
	: serial(serial)
{

}

Ping::Ping(byte* data)
{
	PacketReader r(data);

	r.read(serial);
}

void Ping::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::Ping]);

	w.write(serial);
}

int Ping::size() const
{
	return 9;
}

String Ping::toString() const
{
	return String("PING");
}