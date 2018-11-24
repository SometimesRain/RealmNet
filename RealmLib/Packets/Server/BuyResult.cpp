#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "Packets/PacketWriter.h"
#include "Packets/PacketReader.h"

#include <Packets/BuyResult.h>

BuyResult::BuyResult(int result, const String& message)
	: result(result), message(message)
{

}

BuyResult::BuyResult(byte* data)
{
	PacketReader r(data);

	r.read(result);
	r.read(message);
}

void BuyResult::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::BuyResult]);

	w.write(result);
	w.write(message);
}

int BuyResult::size() const
{
	return 11 + message.length;
}

String BuyResult::toString() const
{
	return String("BUYRESULT");
}