#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"
#include "PacketReader.h"

#include <Packets/JoinGuild.h>

JoinGuild::JoinGuild(const String& guildName)
	: guildName(guildName)
{

}

JoinGuild::JoinGuild(byte* data)
{
	PacketReader r(data);

	r.read(guildName);
}

void JoinGuild::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::JoinGuild]);

	w.write(guildName);
}

int JoinGuild::size() const
{
	return 7 + guildName.length;
}

String JoinGuild::toString() const
{
	return String("JOINGUILD");
}