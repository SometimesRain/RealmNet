#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"
#include "PacketReader.h"

#include <Packets/PetYardUpdate.h>

PetYardUpdate::PetYardUpdate(int type)
	: type(type)
{

}

PetYardUpdate::PetYardUpdate(byte* data)
{
	PacketReader r(data);

	r.read(type);
}

void PetYardUpdate::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::PetYardUpdate]);

	w.write(type);
}

int PetYardUpdate::size() const
{
	return 9;
}

String PetYardUpdate::toString() const
{
	return String("PETYARDUPDATE");
}