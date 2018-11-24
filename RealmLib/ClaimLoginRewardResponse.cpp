#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"
#include "PacketReader.h"

#include <Packets/ClaimLoginRewardResponse.h>

ClaimLoginRewardResponse::ClaimLoginRewardResponse(int itemId, int quantity, int gold)
	: itemId(itemId), quantity(quantity), gold(gold)
{

}

ClaimLoginRewardResponse::ClaimLoginRewardResponse(byte* data)
{
	PacketReader r(data);

	r.read(itemId);
	r.read(quantity);
	r.read(gold);
}

void ClaimLoginRewardResponse::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::ClaimLoginRewardResponse]);

	w.write(itemId);
	w.write(quantity);
	w.write(gold);
}

int ClaimLoginRewardResponse::size() const
{
	return 17;
}

String ClaimLoginRewardResponse::toString() const
{
	return String("CLAIMLOGINREWARDRESPONSE");
}