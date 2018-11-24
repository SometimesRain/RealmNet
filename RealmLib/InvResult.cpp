#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"
#include "PacketReader.h"

#include <Packets/InvResult.h>

InvResult::InvResult(int result)
	: result(result)
{

}

InvResult::InvResult(byte* data)
{
	PacketReader r(data);

	r.read(result);
}

void InvResult::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::InvResult]);

	w.write(result);
}

int InvResult::size() const
{
	return 9;
}

String InvResult::toString() const
{
	return String("INVRESULT");
}