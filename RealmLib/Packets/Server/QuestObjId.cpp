#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "Packets/PacketWriter.h"
#include "Packets/PacketReader.h"

#include <Packets/QuestObjId.h>

QuestObjId::QuestObjId(int objectId)
	: objectId(objectId)
{

}

QuestObjId::QuestObjId(byte* data)
{
	PacketReader r(data);

	r.read(objectId);
}

void QuestObjId::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::QuestObjId]);

	w.write(objectId);
}

int QuestObjId::size() const
{
	return 9;
}

String QuestObjId::toString() const
{
	return String("QUESTOBJID");
}