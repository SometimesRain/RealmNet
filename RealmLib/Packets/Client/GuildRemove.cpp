#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "Packets/PacketWriter.h"
#include "Packets/PacketReader.h"

#include <Packets/GuildRemove.h>

GuildRemove::GuildRemove(const String& name)
	: name(name)
{

}

GuildRemove::GuildRemove(byte* data)
{
	PacketReader r(data);

	r.read(name);
}

void GuildRemove::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::GuildRemove]);

	w.write(name);
}

int GuildRemove::size() const
{
	return 7 + name.length;
}

String GuildRemove::toString() const
{
	return String("GUILDREMOVE");
}