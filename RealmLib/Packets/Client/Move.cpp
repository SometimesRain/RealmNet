#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "Packets/PacketWriter.h"
#include "Packets/PacketReader.h"

#include <Packets/Move.h>

Move::Move(int tickId, int time, const Location& newPosition)
	: tickId(tickId), time(time), newPosition(newPosition)
{

}

Move::Move(int tickId, int time, const Location& newPosition, const Array<MoveRecord>& records)
	: tickId(tickId), time(time), newPosition(newPosition), records(records)
{

}

Move::Move(byte* data)
{
	PacketReader r(data);

	r.read(tickId);
	r.read(time);
	r.read(newPosition);
	r.read(records);
}

void Move::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::Move]);

	w.write(tickId);
	w.write(time);
	w.write(newPosition);
	w.write(records);
}

int Move::size() const
{
	return 23 + 12 * records.length;
}

String Move::toString() const
{
	return String("MOVE");
}