#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"
#include "PacketReader.h"

#include <Packets/ActivePetUpdate.h>

ActivePetUpdate::ActivePetUpdate(int instanceId)
	: instanceId(instanceId)
{

}

ActivePetUpdate::ActivePetUpdate(byte* data)
{
	PacketReader r(data);

	r.read(instanceId);
}

void ActivePetUpdate::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::ActivePetUpdate]);

	w.write(instanceId);
}

int ActivePetUpdate::size() const
{
	return 9;
}

String ActivePetUpdate::toString() const
{
	return String("ACTIVEPETUPDATE");
}