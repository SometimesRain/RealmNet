#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"

#include <Packets/AcceptArenaDeath.h>

AcceptArenaDeath::AcceptArenaDeath()
{

}

AcceptArenaDeath::AcceptArenaDeath(byte* data)
{

}

void AcceptArenaDeath::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::AcceptArenaDeath]);
}

int AcceptArenaDeath::size() const
{
	return 5;
}

String AcceptArenaDeath::toString() const
{
	return String("ACCEPTARENADEATH");
}