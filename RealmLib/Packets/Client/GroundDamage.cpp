#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "Packets/PacketWriter.h"
#include "Packets/PacketReader.h"

#include <Packets/GroundDamage.h>

GroundDamage::GroundDamage(int time, float x, float y)
	: time(time), position(x, y)
{

}

GroundDamage::GroundDamage(int time, const Location& position)
	: time(time), position(position)
{

}

GroundDamage::GroundDamage(byte* data)
{
	PacketReader r(data);

	r.read(time);
	r.read(position);
}

void GroundDamage::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::GroundDamage]);

	w.write(time);
	w.write(position);
}

int GroundDamage::size() const
{
	return 17;
}

String GroundDamage::toString() const
{
	return String("GROUNDDAMAGE");
}