#pragma once

#include <Packets/Packet.h>
#include <DataObjects/Location.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API PlayerShoot : public ClientPacket
{
public:
	int time;
	byte bulletId;
	short itemType;
	Location position;
	float angle;

	PlayerShoot(int time, byte bulletId, short itemType, const Location& position, float angle);
	PlayerShoot(byte* data);

	void emplace(byte* buffer) const override;
	int size() const override;
	String toString() const override;
};