#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "Packets/PacketWriter.h"
#include "Packets/PacketReader.h"

#include <Packets/InvitedToGuild.h>

InvitedToGuild::InvitedToGuild(const String& name, const String& guildName)
	: name(name), guildName(guildName)
{

}

InvitedToGuild::InvitedToGuild(byte* data)
{
	PacketReader r(data);

	r.read(name);
	r.read(guildName);
}

void InvitedToGuild::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::InvitedToGuild]);

	w.write(name);
	w.write(guildName);
}

int InvitedToGuild::size() const
{
	return 9 + name.length + guildName.length;
}

String InvitedToGuild::toString() const
{
	return String("INVITEDTOGUILD");
}