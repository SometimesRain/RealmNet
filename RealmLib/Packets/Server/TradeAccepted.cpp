#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "Packets/PacketWriter.h"
#include "Packets/PacketReader.h"

#include <Packets/TradeAccepted.h>

TradeAccepted::TradeAccepted(const Array<bool>& myOffer, const Array<bool>& yourOffer)
	: myOffer(myOffer), yourOffer(yourOffer)
{

}

TradeAccepted::TradeAccepted(byte* data)
{
	PacketReader r(data);

	r.read(myOffer);
	r.read(yourOffer);
}

void TradeAccepted::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::TradeAccepted]);

	w.write(myOffer);
	w.write(yourOffer);
}

int TradeAccepted::size() const
{
	return 9 + myOffer.length + yourOffer.length;
}

String TradeAccepted::toString() const
{
	return String("TRADEACCEPTED");
}