#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"
#include "PacketReader.h"

#include <Packets/UseItem.h>

UseItem::UseItem(int time, const SlotObject& slotObject, const Location& position, byte useType)
	: position(position), time(time), slotObject(slotObject), useType(useType)
{

}

UseItem::UseItem(int time, const SlotObject& slotObject, float x, float y, byte useType)
	: position(x, y), time(time), slotObject(slotObject), useType(useType)
{

}

UseItem::UseItem(byte* data)
{
	PacketReader r(data);

	r.read(time);
	r.read(slotObject);
	r.read(position);
	r.read(useType);
}

void UseItem::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::UseItem]);

	w.write(time);
	w.write(slotObject);
	w.write(position);
	w.write(useType);
}

int UseItem::size() const
{
	return 27;
}

String UseItem::toString() const
{
	return String("USEITEM");
}