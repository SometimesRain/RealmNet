#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "Packets/PacketWriter.h"
#include "Packets/PacketReader.h"

#include <Packets/Pong.h>

Pong::Pong(int serial, int time)
	: serial(serial), time(time)
{

}

Pong::Pong(byte* data)
{
	PacketReader r(data);

	r.read(serial);
	r.read(time);
}

void Pong::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::Pong]);

	w.write(serial);
	w.write(time);
}

int Pong::size() const
{
	return 13;
}

String Pong::toString() const
{
	return String("PONG");
}