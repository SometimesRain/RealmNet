#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"
#include "PacketReader.h"

#include <Packets/Buy.h>

Buy::Buy(int objectId, int quantity)
	: objectId(objectId), quantity(quantity)
{

}

Buy::Buy(byte* data)
{
	PacketReader r(data);

	r.read(objectId);
	r.read(quantity);
}

void Buy::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::Buy]);

	w.write(objectId);
	w.write(quantity);
}

int Buy::size() const
{
	return 13;
}

String Buy::toString() const
{
	return String("BUY");
}