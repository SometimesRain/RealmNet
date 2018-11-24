#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "Packets/PacketWriter.h"
#include "Packets/PacketReader.h"

#include <Packets/ChangePetSkin.h>

ChangePetSkin::ChangePetSkin(int petId, int skinType, int currency)
	: petId(petId), skinType(skinType), currency(currency)
{

}

ChangePetSkin::ChangePetSkin(byte* data)
{
	PacketReader r(data);

	r.read(petId);
	r.read(skinType);
	r.read(currency);
}

void ChangePetSkin::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::ChangePetSkin]);

	w.write(petId);
	w.write(skinType);
	w.write(currency);
}

int ChangePetSkin::size() const
{
	return 17;
}

String ChangePetSkin::toString() const
{
	return String("CHANGEPETSKIN");
}