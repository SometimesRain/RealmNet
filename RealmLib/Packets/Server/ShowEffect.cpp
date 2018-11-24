#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "Packets/PacketWriter.h"
#include "Packets/PacketReader.h"

#include <Packets/ShowEffect.h>

ShowEffect::ShowEffect(byte effectType, int targetId, const Location& pos1, const Location& pos2, int color, float duration)
	: effectType(effectType), targetId(targetId), pos1(pos1), pos2(pos2), color(color), duration(duration)
{

}

ShowEffect::ShowEffect(byte* data)
{
	PacketReader r(data);

	r.read(effectType);
	r.read(targetId);
	r.read(pos1);
	r.read(pos2);
	r.read(color);
	r.read(duration);
}

void ShowEffect::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::ShowEffect]);

	w.write(effectType);
	w.write(targetId);
	w.write(pos1);
	w.write(pos2);
	w.write(color);
	w.write(duration);
}

int ShowEffect::size() const
{
	return 34;
}

String ShowEffect::toString() const
{
	return String("SHOWEFFECT");
}