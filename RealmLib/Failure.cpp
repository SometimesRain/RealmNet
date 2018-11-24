#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"
#include "PacketReader.h"

#include <Packets/Failure.h>

Failure::Failure(int errorId, const String& message)
	: errorId(errorId), message(message)
{

}

Failure::Failure(byte* data)
{
	PacketReader r(data);

	r.read(errorId);
	r.read(message);
}

void Failure::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::Failure]);

	w.write(errorId);
	w.write(message);
}

int Failure::size() const
{
	return 11 + message.length;
}

String Failure::toString() const
{
	return String("FAILURE");
}