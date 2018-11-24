#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "Packets/PacketWriter.h"
#include "Packets/PacketReader.h"

#include <Packets/Create.h>

Create::Create(ushort classType)
	: classType(classType), skinType(0)
{

}

Create::Create(ushort classType, ushort skinType)
	: classType(classType), skinType(skinType)
{

}

Create::Create(byte* data)
{
	PacketReader r(data);

	r.read(classType);
	r.read(skinType);
}

void Create::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::Create]);

	w.write(classType);
	w.write(skinType);
}

int Create::size() const
{
	return 9;
}

String Create::toString() const
{
	return String("CREATE");
}