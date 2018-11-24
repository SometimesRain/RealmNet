#pragma once

#include <Packets/Packet.h>
#include <DataObjects/Location.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API EnemyShoot : public ServerPacket
{
public:
	byte bulletId;
	int ownerId;
	byte bulletType;
	Location position;
	float angle;
	short damage;
	byte numShots;
	float angleInc;

	EnemyShoot(byte bulletId, int ownerId, byte bulletType, const Location& position, float angle, short damage, byte numShots, float angleInc);
	EnemyShoot(byte* data);

	void emplace(byte* buffer) const override;
	int size() const override;
	String toString() const override;
};