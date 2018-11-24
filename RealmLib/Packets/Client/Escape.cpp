#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "Packets/PacketWriter.h"

#include <Packets/Escape.h>

Escape::Escape()
{

}

Escape::Escape(byte* data)
{

}

void Escape::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::Escape]);
}

int Escape::size() const
{
	return 5;
}

String Escape::toString() const
{
	return String("ESCAPE");
}