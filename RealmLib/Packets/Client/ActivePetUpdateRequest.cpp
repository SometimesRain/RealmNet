#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "Packets/PacketWriter.h"
#include "Packets/PacketReader.h"

#include <Packets/ActivePetUpdateRequest.h>

ActivePetUpdateRequest::ActivePetUpdateRequest(byte commandType, int instanceId)
	: commandType(commandType), instanceId(instanceId)
{

}

ActivePetUpdateRequest::ActivePetUpdateRequest(byte* data)
{
	PacketReader r(data);

	r.read(commandType);
	r.read(instanceId);
}

void ActivePetUpdateRequest::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::ActivePetUpdateRequest]);

	w.write(commandType);
	w.write(instanceId);
}

int ActivePetUpdateRequest::size() const
{
	return 10;
}

String ActivePetUpdateRequest::toString() const
{
	return String("ACTIVEPETUPDATEREQUEST");
}