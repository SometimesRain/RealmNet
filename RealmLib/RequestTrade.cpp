#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"
#include "PacketReader.h"

#include <Packets/RequestTrade.h>

RequestTrade::RequestTrade(const String& name)
	: name(name)
{

}

RequestTrade::RequestTrade(byte* data)
{
	PacketReader r(data);

	r.read(name);
}

void RequestTrade::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::RequestTrade]);

	w.write(name);
}

int RequestTrade::size() const
{
	return 7 + name.length;
}

String RequestTrade::toString() const
{
	return String("REQUESTTRADE");
}