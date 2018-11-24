#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"
#include "PacketReader.h"

#include <Packets/ArenaNextWave.h>

ArenaNextWave::ArenaNextWave(int currentRuntime)
	: currentRuntime(currentRuntime)
{

}

ArenaNextWave::ArenaNextWave(byte* data)
{
	PacketReader r(data);

	r.read(currentRuntime);
}

void ArenaNextWave::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::ArenaNextWave]);

	w.write(currentRuntime);
}

int ArenaNextWave::size() const
{
	return 9;
}

String ArenaNextWave::toString() const
{
	return String("ARENANEXTWAVE");
}