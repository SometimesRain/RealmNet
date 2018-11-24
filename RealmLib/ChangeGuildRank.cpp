#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"
#include "PacketReader.h"

#include <Packets/ChangeGuildRank.h>

ChangeGuildRank::ChangeGuildRank(const String& name, int guildRank)
	: name(name), guildRank(guildRank)
{

}

ChangeGuildRank::ChangeGuildRank(byte* data)
{
	PacketReader r(data);

	r.read(name);
	r.read(guildRank);
}

void ChangeGuildRank::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::ChangeGuildRank]);

	w.write(name);
	w.write(guildRank);
}

int ChangeGuildRank::size() const
{
	return 11 + name.length;
}

String ChangeGuildRank::toString() const
{
	return String("CHANGEGUILDRANK");
}