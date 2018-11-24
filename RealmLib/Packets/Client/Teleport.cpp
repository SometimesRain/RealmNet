#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "Packets/PacketWriter.h"
#include "Packets/PacketReader.h"

#include <Packets/Teleport.h>

Teleport::Teleport(int objectId)
	: objectId(objectId)
{

}

Teleport::Teleport(byte* data)
{
	PacketReader r(data);

	r.read(objectId);
}

void Teleport::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::Teleport]);

	w.write(objectId);
}

int Teleport::size() const
{
	return 9;
}

String Teleport::toString() const
{
	return String("TELEPORT");
}