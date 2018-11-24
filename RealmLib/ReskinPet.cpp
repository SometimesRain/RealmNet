#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"
#include "PacketReader.h"

#include <Packets/ReskinPet.h>

ReskinPet::ReskinPet(int instanceId, int newPetType, const SlotObject& item)
	: instanceId(instanceId), newPetType(newPetType), item(item)
{

}

ReskinPet::ReskinPet(byte* data)
{
	PacketReader r(data);

	r.read(instanceId);
	r.read(newPetType);
	r.read(item);
}

void ReskinPet::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::ReskinPet]);

	w.write(instanceId);
	w.write(newPetType);
	w.write(item);
}

int ReskinPet::size() const
{
	return 21;
}

String ReskinPet::toString() const
{
	return String("RESKINPET");
}