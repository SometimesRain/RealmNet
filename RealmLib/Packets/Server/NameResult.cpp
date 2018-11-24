#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "Packets/PacketWriter.h"
#include "Packets/PacketReader.h"

#include <Packets/NameResult.h>

NameResult::NameResult(bool success, const String& errorMessage)
	: success(success), errorMessage(errorMessage)
{

}

NameResult::NameResult(byte* data)
{
	PacketReader r(data);

	r.read(success);
	r.read(errorMessage);
}

void NameResult::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::NameResult]);

	w.write(success);
	w.write(errorMessage);
}

int NameResult::size() const
{
	return 8 + errorMessage.length;
}

String NameResult::toString() const
{
	return String("NAMERESULT");
}