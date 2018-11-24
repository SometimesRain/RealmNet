#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"
#include "PacketReader.h"

#include <Packets/PetHatched.h>

PetHatched::PetHatched(const String& name, int skin, int itemType)
	: name(name), skin(skin), itemType(itemType)
{

}

PetHatched::PetHatched(byte* data)
{
	PacketReader r(data);

	r.read(name);
	r.read(skin);
	r.read(itemType);
}

void PetHatched::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::PetHatched]);

	w.write(name);
	w.write(skin);
	w.write(itemType);
}

int PetHatched::size() const
{
	return 15 + name.length;
}

String PetHatched::toString() const
{
	return String("PETHATCHED");
}