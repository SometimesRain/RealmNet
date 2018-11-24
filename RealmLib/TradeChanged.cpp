#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"
#include "PacketReader.h"

#include <Packets/TradeChanged.h>

TradeChanged::TradeChanged(const Array<bool>& offer)
	: offer(offer)
{

}

TradeChanged::TradeChanged(byte* data)
{
	PacketReader r(data);

	r.read(offer);
}

void TradeChanged::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::TradeChanged]);

	w.write(offer);
}

int TradeChanged::size() const
{
	return 7 + offer.length;
}

String TradeChanged::toString() const
{
	return String("TRADECHANGED");
}