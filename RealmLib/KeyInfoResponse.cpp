#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"
#include "PacketReader.h"

#include <Packets/KeyInfoResponse.h>

KeyInfoResponse::KeyInfoResponse(const String& name, const String& description, const String& creator)
	: name(name), description(description), creator(creator)
{

}

KeyInfoResponse::KeyInfoResponse(byte* data)
{
	PacketReader r(data);

	r.read(name);
	r.read(description);
	r.read(creator);
}

void KeyInfoResponse::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::KeyInfoResponse]);

	w.write(name);
	w.write(description);
	w.write(creator);
}

int KeyInfoResponse::size() const
{
	return 11 + name.length + description.length + creator.length;
}

String KeyInfoResponse::toString() const
{
	return String("KEYINFORESPONSE");
}