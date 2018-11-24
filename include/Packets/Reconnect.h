#pragma once

#include <Packets/Packet.h>
#include <DataObjects/Array.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API Reconnect : public ServerPacket
{
public:
	String name;
	String host;
	String stats;
	int port;
	int gameId;
	int keyTime;
	bool isFromArena;
	Array<byte> key;

	Reconnect(const String& name, const String& host, int gameId);
	Reconnect(const String& name, const String& host, int gameId, int keyTime, const Array<byte>& key);
	Reconnect(byte* data);

	void emplace(byte* buffer) const override;
	int size() const override;
	String toString() const override;
};