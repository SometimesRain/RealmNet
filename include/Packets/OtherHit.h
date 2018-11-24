#pragma once

#include <Packets/Packet.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API OtherHit : public ClientPacket
{
public:
	int time;
	byte bulletId;
	int objectId;
	int targetId;

	OtherHit(int time, byte bulletId, int objectId, int targetId);
	OtherHit(byte* data);

	void emplace(byte* buffer) const override;
	int size() const override;
	String toString() const override;
};