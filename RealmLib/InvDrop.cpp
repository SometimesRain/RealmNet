#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"
#include "PacketReader.h"

#include <Packets/InvDrop.h>

InvDrop::InvDrop(const SlotObject& slot)
	: slot(slot)
{

}

InvDrop::InvDrop(byte* data)
{
	PacketReader r(data);

	r.read(slot);
}

void InvDrop::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::InvDrop]);

	w.write(slot);
}

int InvDrop::size() const
{
	return 14;
}

String InvDrop::toString() const
{
	return String("INVDROP");
}