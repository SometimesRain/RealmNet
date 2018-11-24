#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"
#include "PacketReader.h"

#include <Packets/Death.h>

Death::Death(const String& accountId, int charId, const String& killedBy, int zombieType, int zombieId)
	: accountId(accountId), charId(charId), killedBy(killedBy), zombieType(zombieType), zombieId(zombieId)
{

}

Death::Death(byte* data)
{
	PacketReader r(data);

	r.read(accountId);
	r.read(charId);
	r.read(killedBy);
	r.read(zombieType);
	r.read(zombieId);
}

void Death::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::Death]);

	w.write(accountId);
	w.write(charId);
	w.write(killedBy);
	w.write(zombieType);
	w.write(zombieId);
}

int Death::size() const
{
	return 21 + accountId.length + killedBy.length;
}

String Death::toString() const
{
	return String("DEATH");
}