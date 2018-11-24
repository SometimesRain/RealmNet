#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"
#include "PacketReader.h"

#include <Packets/AcceptTrade.h>

AcceptTrade::AcceptTrade(const Array<bool>& myOffer, const Array<bool>& yourOffer)
	: myOffer(myOffer), yourOffer(yourOffer)
{

}

AcceptTrade::AcceptTrade(byte* data)
{
	PacketReader r(data);

	r.read(myOffer);
	r.read(yourOffer);
}

void AcceptTrade::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::AcceptTrade]);

	w.write(myOffer);
	w.write(yourOffer);
}

int AcceptTrade::size() const
{
	return 9 + myOffer.length + yourOffer.length;
}

String AcceptTrade::toString() const
{
	return String("ACCEPTTRADE");
}