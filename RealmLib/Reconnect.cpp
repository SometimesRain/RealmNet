#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"
#include "PacketReader.h"

#include <Packets/Reconnect.h>

Reconnect::Reconnect(const String& name, const String& host, int gameId)
	: name(name), host(host), gameId(gameId), port(2050), keyTime(-1), isFromArena(false)
{

}

Reconnect::Reconnect(const String& name, const String& host, int gameId, int keyTime, const Array<byte>& key)
	: name(name), host(host), gameId(gameId), port(2050), keyTime(keyTime), key(key), isFromArena(false)
{

}

Reconnect::Reconnect(byte* data)
{
	PacketReader r(data);

	r.read(name);
	r.read(host);
	r.read(stats);
	r.read(port);
	r.read(gameId);
	r.read(keyTime);
	r.read(isFromArena);
	r.read(key);
}

void Reconnect::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::Reconnect]);

	w.write(name);
	w.write(host);
	w.write(stats);
	w.write(port);
	w.write(gameId);
	w.write(keyTime);
	w.write(isFromArena);
	w.write(key);
}

int Reconnect::size() const
{
	return 26 + name.length + host.length + stats.length + key.length;
}

String Reconnect::toString() const
{
	return String("RECONNECT");
}