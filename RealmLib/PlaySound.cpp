#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"
#include "PacketReader.h"

#include <Packets/PlaySound.h>

PlaySound::PlaySound(int ownerId, byte soundId)
	: ownerId(ownerId), soundId(soundId)
{

}

PlaySound::PlaySound(byte* data)
{
	PacketReader r(data);

	r.read(ownerId);
	r.read(soundId);
}

void PlaySound::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::PlaySound]);

	w.write(ownerId);
	w.write(soundId);
}

int PlaySound::size() const
{
	return 10;
}

String PlaySound::toString() const
{
	return String("PLAYSOUND");
}