#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"
#include "PacketReader.h"

#include <Packets/ReskinUnlock.h>

ReskinUnlock::ReskinUnlock(int skinId, int isPetSkin)
	: skinId(skinId), isPetSkin(isPetSkin)
{

}

ReskinUnlock::ReskinUnlock(byte* data)
{
	PacketReader r(data);

	r.read(skinId);
	r.read(isPetSkin);
}

void ReskinUnlock::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::ReskinUnlock]);

	w.write(skinId);
	w.write(isPetSkin);
}

int ReskinUnlock::size() const
{
	return 13;
}

String ReskinUnlock::toString() const
{
	return String("RESKINUNLOCK");
}