#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "Packets/PacketWriter.h"

#include <Packets/UpdateAck.h>

UpdateAck::UpdateAck()
{

}

UpdateAck::UpdateAck(byte* data)
{

}

void UpdateAck::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::UpdateAck]);
}

int UpdateAck::size() const
{
	return 5;
}

String UpdateAck::toString() const
{
	return String("UPDATEACK");
}