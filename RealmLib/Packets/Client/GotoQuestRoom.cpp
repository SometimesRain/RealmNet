#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "Packets/PacketWriter.h"

#include <Packets/GotoQuestRoom.h>

GotoQuestRoom::GotoQuestRoom()
{

}

GotoQuestRoom::GotoQuestRoom(byte* data)
{

}

void GotoQuestRoom::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::GotoQuestRoom]);
}

int GotoQuestRoom::size() const
{
	return 5;
}

String GotoQuestRoom::toString() const
{
	return String("GOTOQUESTROOM");
}