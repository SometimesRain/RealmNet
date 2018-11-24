#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "Packets/PacketWriter.h"
#include "Packets/PacketReader.h"

#include <Packets/NewAbilityUnlocked.h>

NewAbilityUnlocked::NewAbilityUnlocked(int type)
	: type(type)
{

}

NewAbilityUnlocked::NewAbilityUnlocked(byte* data)
{
	PacketReader r(data);

	r.read(type);
}

void NewAbilityUnlocked::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::NewAbilityUnlocked]);

	w.write(type);
}

int NewAbilityUnlocked::size() const
{
	return 9;
}

String NewAbilityUnlocked::toString() const
{
	return String("NEWABILITYUNLOCKED");
}