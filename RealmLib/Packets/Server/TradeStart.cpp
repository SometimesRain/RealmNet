#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "Packets/PacketWriter.h"
#include "Packets/PacketReader.h"

#include <Packets/TradeStart.h>

TradeStart::TradeStart(const Array<TradeItem>& myItems, const String& yourName, const Array<TradeItem>& yourItems)
	: myItems(myItems), yourName(yourName), yourItems(yourItems)
{

}

TradeStart::TradeStart(byte* data)
{
	PacketReader r(data);

	r.read(myItems);
	r.read(yourName);
	r.read(yourItems);
}

void TradeStart::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::TradeStart]);

	w.write(myItems);
	w.write(yourName);
	w.write(yourItems);
}

int TradeStart::size() const
{
	return 11 + yourName.length + 10 * (myItems.length + yourItems.length);
}

String TradeStart::toString() const
{
	return String("TRADESTART");
}