#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "Packets/PacketWriter.h"
#include "Packets/PacketReader.h"

#include <Packets/GuildInvite.h>

GuildInvite::GuildInvite(const String& name)
	: name(name)
{

}

GuildInvite::GuildInvite(byte* data)
{
	PacketReader r(data);

	r.read(name);
}

void GuildInvite::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::GuildInvite]);

	w.write(name);
}

int GuildInvite::size() const
{
	return 7 + name.length;
}

String GuildInvite::toString() const
{
	return String("GUILDINVITE");
}