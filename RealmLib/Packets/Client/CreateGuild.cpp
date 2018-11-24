#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "Packets/PacketWriter.h"
#include "Packets/PacketReader.h"

#include <Packets/CreateGuild.h>

CreateGuild::CreateGuild(const String& name)
	: name(name)
{

}

CreateGuild::CreateGuild(byte* data)
{
	PacketReader r(data);

	r.read(name);
}

void CreateGuild::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::CreateGuild]);

	w.write(name);
}

int CreateGuild::size() const
{
	return 7 + name.length;
}

String CreateGuild::toString() const
{
	return String("CREATEGUILD");
}