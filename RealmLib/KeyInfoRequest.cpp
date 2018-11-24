#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"
#include "PacketReader.h"

#include <Packets/KeyInfoRequest.h>

KeyInfoRequest::KeyInfoRequest(int itemType)
	: itemType(itemType)
{

}

KeyInfoRequest::KeyInfoRequest(byte* data)
{
	PacketReader r(data);

	r.read(itemType);
}

void KeyInfoRequest::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::KeyInfoRequest]);

	w.write(itemType);
}

int KeyInfoRequest::size() const
{
	return 9;
}

String KeyInfoRequest::toString() const
{
	return String("KEYINFOREQUEST");
}