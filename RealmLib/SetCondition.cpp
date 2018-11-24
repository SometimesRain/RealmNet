#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"
#include "PacketReader.h"

#include <Packets/SetCondition.h>

SetCondition::SetCondition(byte effect, float duration)
	: effect(effect), duration(duration)
{

}

SetCondition::SetCondition(byte* data)
{
	PacketReader r(data);

	r.read(effect);
	r.read(duration);
}

void SetCondition::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::SetCondition]);

	w.write(effect);
	w.write(duration);
}

int SetCondition::size() const
{
	return 10;
}

String SetCondition::toString() const
{
	return String("SETCONDITION");
}