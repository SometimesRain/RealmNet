#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "Packets/PacketWriter.h"
#include "Packets/PacketReader.h"

#include <Packets/ClaimLoginReward.h>

ClaimLoginReward::ClaimLoginReward(const String& claimKey, const String& type)
	: claimKey(claimKey), type(type)
{

}

ClaimLoginReward::ClaimLoginReward(byte* data)
{
	PacketReader r(data);

	r.read(claimKey);
	r.read(type);
}

void ClaimLoginReward::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::ClaimLoginReward]);

	w.write(claimKey);
	w.write(type);
}

int ClaimLoginReward::size() const
{
	return 9 + claimKey.length + type.length;
}

String ClaimLoginReward::toString() const
{
	return String("CLAIMLOGINREWARD");
}