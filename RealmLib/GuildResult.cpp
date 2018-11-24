#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"
#include "PacketReader.h"

#include <Packets/GuildResult.h>

GuildResult::GuildResult(bool success, const String& json)
	: success(success), json(json)
{

}

GuildResult::GuildResult(byte* data)
{
	PacketReader r(data);

	r.read(success);
	r.read(json);
}

void GuildResult::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::GuildResult]);

	w.write(success);
	w.write(json);
}

int GuildResult::size() const
{
	return 8 + json.length;
}

String GuildResult::toString() const
{
	return String("GUILDRESULT");
}