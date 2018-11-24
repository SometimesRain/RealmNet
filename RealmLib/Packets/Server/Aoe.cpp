#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "Packets/PacketWriter.h"
#include "Packets/PacketReader.h"

#include <Packets/Aoe.h>

Aoe::Aoe(const Location& position, float radius, ushort damage, byte effect, float duration, ushort originType, int color)
	: position(position), radius(radius), damage(damage), effect(effect), duration(duration), originType(originType), color(color)
{

}

Aoe::Aoe(byte* data)
{
	PacketReader r(data);

	r.read(position);
	r.read(radius);
	r.read(damage);
	r.read(effect);
	r.read(duration);
	r.read(originType);
	r.read(color);
}

void Aoe::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::Aoe]);

	w.write(position);
	w.write(radius);
	w.write(damage);
	w.write(effect);
	w.write(duration);
	w.write(originType);
	w.write(color);
}

int Aoe::size() const
{
	return 30;
}

String Aoe::toString() const
{
	return String("AOE");
}