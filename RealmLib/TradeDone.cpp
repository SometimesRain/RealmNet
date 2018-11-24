#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"
#include "PacketReader.h"

#include <Packets/TradeDone.h>

TradeDone::TradeDone(int result, const String& message)
	: result(result), message(message)
{

}

TradeDone::TradeDone(byte* data)
{
	PacketReader r(data);

	r.read(result);
	r.read(message);
}

void TradeDone::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::TradeDone]);

	w.write(result);
	w.write(message);
}

int TradeDone::size() const
{
	return 11 + message.length;
}

String TradeDone::toString() const
{
	return String("TRADEDONE");
}