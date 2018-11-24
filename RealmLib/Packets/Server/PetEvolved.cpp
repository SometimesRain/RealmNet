#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "Packets/PacketWriter.h"
#include "Packets/PacketReader.h"

#include <Packets/PetEvolved.h>

PetEvolved::PetEvolved(int petId, int initialSkin, int finalSkin)
	: petId(petId), initialSkin(initialSkin), finalSkin(finalSkin)
{

}

PetEvolved::PetEvolved(byte* data)
{
	PacketReader r(data);

	r.read(petId);
	r.read(initialSkin);
	r.read(finalSkin);
}

void PetEvolved::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::PetEvolved]);

	w.write(petId);
	w.write(initialSkin);
	w.write(finalSkin);
}

int PetEvolved::size() const
{
	return 17;
}

String PetEvolved::toString() const
{
	return String("PETEVOLVED");
}