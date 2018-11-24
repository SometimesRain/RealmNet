#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"
#include "PacketReader.h"

#include <Packets/TradeRequested.h>

TradeRequested::TradeRequested(const String& name)
	: name(name)
{

}

TradeRequested::TradeRequested(byte* data)
{
	PacketReader r(data);

	r.read(name);
}

void TradeRequested::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::TradeRequested]);

	w.write(name);
}

int TradeRequested::size() const
{
	return 7 + name.length;
}

String TradeRequested::toString() const
{
	return String("TRADEREQUESTED");
}