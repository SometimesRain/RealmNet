#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "Packets/PacketWriter.h"
#include "Packets/PacketReader.h"

#include <Packets/ClientStat.h>

ClientStat::ClientStat(const String& name, int value)
	: name(name), value(value)
{

}

ClientStat::ClientStat(byte* data)
{
	PacketReader r(data);

	r.read(name);
	r.read(value);
}

void ClientStat::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::ClientStat]);

	w.write(name);
	w.write(value);
}

int ClientStat::size() const
{
	return 11 + name.length;
}

String ClientStat::toString() const
{
	return String("CLIENTSTAT");
}