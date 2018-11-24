#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"

#include <Packets/FetchQuest.h>

FetchQuest::FetchQuest()
{

}

FetchQuest::FetchQuest(byte* data)
{

}

void FetchQuest::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::FetchQuest]);
}

int FetchQuest::size() const
{
	return 5;
}

String FetchQuest::toString() const
{
	return String("FETCHQUEST");
}