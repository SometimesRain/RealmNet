#pragma once

#include <Packets/Packet.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API GuildResult : public ServerPacket
{
public:
	bool success;
	String json;

	GuildResult(bool success, const String& json);
	GuildResult(byte* data);

	void emplace(byte* buffer) const override;
	int size() const override;
	String toString() const override;
};