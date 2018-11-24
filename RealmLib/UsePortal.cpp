#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"
#include "PacketReader.h"

#include <Packets/UsePortal.h>

UsePortal::UsePortal(int objectId)
	: objectId(objectId)
{

}

UsePortal::UsePortal(byte* data)
{
	PacketReader r(data);

	r.read(objectId);
}

void UsePortal::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::UsePortal]);

	w.write(objectId);
}

int UsePortal::size() const
{
	return 9;
}

String UsePortal::toString() const
{
	return String("USEPORTAL");
}