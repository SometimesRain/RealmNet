#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"
#include "PacketReader.h"

#include <Packets/Reskin.h>

Reskin::Reskin(int skinId)
	: skinId(skinId)
{

}

Reskin::Reskin(byte* data)
{
	PacketReader r(data);

	r.read(skinId);
}

void Reskin::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::Reskin]);

	w.write(skinId);
}

int Reskin::size() const
{
	return 9;
}

String Reskin::toString() const
{
	return String("RESKIN");
}