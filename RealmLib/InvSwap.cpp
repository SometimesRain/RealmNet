#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"
#include "PacketReader.h"

#include <Packets/InvSwap.h>

InvSwap::InvSwap(int time, const Location& position, const SlotObject& slotObject1, const SlotObject& slotObject2)
	: time(time), position(position), slotObject1(slotObject1), slotObject2(slotObject2)
{

}

InvSwap::InvSwap(int time, float x, float y, const SlotObject& slotObject1, const SlotObject& slotObject2)
	: time(time), position(x, y), slotObject1(slotObject1), slotObject2(slotObject2)
{

}

InvSwap::InvSwap(byte* data)
{
	PacketReader r(data);

	r.read(time);
	r.read(position);
	r.read(slotObject1);
	r.read(slotObject2);
}

void InvSwap::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::InvSwap]);

	w.write(time);
	w.write(position);
	w.write(slotObject1);
	w.write(slotObject2);
}

int InvSwap::size() const
{
	return 35;
}

String InvSwap::toString() const
{
	return String("INVSWAP");
}