#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"
#include "PacketReader.h"

#include <Packets/QuestRedeemResponse.h>

QuestRedeemResponse::QuestRedeemResponse(bool ok, const String& message)
	: ok(ok), message(message)
{

}

QuestRedeemResponse::QuestRedeemResponse(byte* data)
{
	PacketReader r(data);

	r.read(ok);
	r.read(message);
}

void QuestRedeemResponse::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::QuestRedeemResponse]);

	w.write(ok);
	w.write(message);
}

int QuestRedeemResponse::size() const
{
	return 8 + message.length;
}

String QuestRedeemResponse::toString() const
{
	return String("QUESTREDEEMRESPONSE");
}