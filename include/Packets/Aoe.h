#pragma once

#include <Packets/Packet.h>
#include <DataObjects/Location.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API Aoe : public ServerPacket
{
public:
	Location position;
	float radius;
	ushort damage;
	byte effect;
	float duration;
	ushort originType;
	int color;

	Aoe(const Location& position, float radius, ushort damage, byte effect, float duration, ushort originType, int color);
	Aoe(byte* data);

	void emplace(byte* buffer) const override;
	int size() const override;
	String toString() const override;
};