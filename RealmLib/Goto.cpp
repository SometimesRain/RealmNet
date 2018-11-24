#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"
#include "PacketReader.h"

#include <Packets/Goto.h>

Goto::Goto(int objectId, const Location& position)
	: objectId(objectId), position(position)
{

}

Goto::Goto(byte* data)
{
	PacketReader r(data);

	r.read(objectId);
	r.read(position);
}

void Goto::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::Goto]);

	w.write(objectId);
	w.write(position);
}

int Goto::size() const
{
	return 17;
}

String Goto::toString() const
{
	return String("GOTO");
}