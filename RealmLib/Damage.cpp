#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"
#include "PacketReader.h"

#include <Packets/Damage.h>

Damage::Damage(int targetId, const Array<byte>& effects, int damage, bool kill, bool armorPierce, byte bulletId, int objectId)
	: targetId(targetId), effects(effects), damage(damage), kill(kill), armorPierce(armorPierce), bulletId(bulletId), objectId(objectId)
{

}

Damage::Damage(byte* data)
{
	PacketReader r(data);

	r.read(targetId);
	r.read8(effects);
	r.read(damage);
	r.read(kill);
	r.read(armorPierce);
	r.read(bulletId);
	r.read(objectId);
}

void Damage::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::Damage]);

	w.write(targetId);
	w.write8(effects);
	w.write(damage);
	w.write(kill);
	w.write(armorPierce);
	w.write(bulletId);
	w.write(objectId);
}

int Damage::size() const
{
	return 21;
}

String Damage::toString() const
{
	return String("DAMAGE");
}