#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "Packets/PacketWriter.h"
#include "Packets/PacketReader.h"

#include <Packets/ChangeTrade.h>

ChangeTrade::ChangeTrade(const Array<bool>& offer)
	: offer(offer)
{

}

ChangeTrade::ChangeTrade(byte* data)
{
	PacketReader r(data);

	r.read(offer);
}

void ChangeTrade::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::ChangeTrade]);

	w.write(offer);
}

int ChangeTrade::size() const
{
	return 7 + offer.length;
}

String ChangeTrade::toString() const
{
	return String("CHANGETRADE");
}