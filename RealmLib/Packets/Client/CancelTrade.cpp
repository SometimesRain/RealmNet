#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "Packets/PacketWriter.h"

#include <Packets/CancelTrade.h>

CancelTrade::CancelTrade()
{

}

CancelTrade::CancelTrade(byte* data)
{

}

void CancelTrade::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::CancelTrade]);
}

int CancelTrade::size() const
{
	return 5;
}

String CancelTrade::toString() const
{
	return String("CANCELTRADE");
}