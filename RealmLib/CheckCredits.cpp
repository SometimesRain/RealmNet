#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"

#include <Packets/CheckCredits.h>

CheckCredits::CheckCredits()
{

}

CheckCredits::CheckCredits(byte* data)
{

}

void CheckCredits::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::CheckCredits]);
}

int CheckCredits::size() const
{
	return 5;
}

String CheckCredits::toString() const
{
	return String("CHECKCREDITS");
}