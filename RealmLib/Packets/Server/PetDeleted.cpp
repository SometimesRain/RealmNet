#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "Packets/PacketWriter.h"
#include "Packets/PacketReader.h"

#include <Packets/PetDeleted.h>

PetDeleted::PetDeleted(int petId)
	: petId(petId)
{

}

PetDeleted::PetDeleted(byte* data)
{
	PacketReader r(data);

	r.read(petId);
}

void PetDeleted::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::PetDeleted]);

	w.write(petId);
}

int PetDeleted::size() const
{
	return 9;
}

String PetDeleted::toString() const
{
	return String("PETDELETED");
}