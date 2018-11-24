#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "Packets/PacketWriter.h"
#include "Packets/PacketReader.h"

#include <Packets/Load.h>

Load::Load(int charId)
	: charId(charId), isFromArena(false)
{

}

Load::Load(int charId, bool isFromArena)
	: charId(charId), isFromArena(isFromArena)
{

}

Load::Load(byte* data)
{
	PacketReader r(data);

	r.read(charId);
	r.read(isFromArena);
}

void Load::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::Load]);

	w.write(charId);
	w.write(isFromArena);
}

int Load::size() const
{
	return 10;
}

String Load::toString() const
{
	return String("LOAD");
}