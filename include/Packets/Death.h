#pragma once

#include <Packets/Packet.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API Death : public ServerPacket
{
public:
	String accountId;
	int charId;
	String killedBy;
	int zombieType;
	int zombieId;

	Death(const String& accountId, int charId, const String& killedBy, int zombieType, int zombieId);
	Death(byte* data);

	void emplace(byte* buffer) const override;
	int size() const override;
	String toString() const override;
};