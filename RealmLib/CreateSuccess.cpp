#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"
#include "PacketReader.h"

#include <Packets/CreateSuccess.h>

CreateSuccess::CreateSuccess(int objectId, int charId)
	: objectId(objectId), charId(charId)
{

}

CreateSuccess::CreateSuccess(byte* data)
{
	PacketReader r(data);

	r.read(objectId);
	r.read(charId);
}

void CreateSuccess::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::CreateSuccess]);

	w.write(objectId);
	w.write(charId);
}

int CreateSuccess::size() const
{
	return 13;
}

String CreateSuccess::toString() const
{
	return String("CREATESUCCESS");
}