#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"
#include "PacketReader.h"

#include <Packets/EnterArena.h>

EnterArena::EnterArena(int currency)
	: currency(currency)
{

}

EnterArena::EnterArena(byte* data)
{
	PacketReader r(data);

	r.read(currency);
}

void EnterArena::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::EnterArena]);

	w.write(currency);
}

int EnterArena::size() const
{
	return 9;
}

String EnterArena::toString() const
{
	return String("ENTERARENA");
}