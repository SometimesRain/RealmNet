#pragma once

#include <Packets/Packet.h>
#include <DataObjects/Location.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API ServerPlayerShoot : public ServerPacket
{
public:
	byte bulletId;
	int ownerId;
	int item;
	Location startPos;
	float angle;
	short damage;

	ServerPlayerShoot(byte bulletId, int ownerId, int item, const Location& startPos, float angle, short damage);
	ServerPlayerShoot(byte* data);

	void emplace(byte* buffer) const override;
	int size() const override;
	String toString() const override;
};