#pragma once

#include <Packets/Packet.h>
#include <DataObjects/Location.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API ShowEffect : public ServerPacket
{
public:
	byte effectType;
	int targetId;
	Location pos1;
	Location pos2;
	int color;
	float duration;

	ShowEffect(byte effectType, int targetId, const Location& pos1, const Location& pos2, int color, float duration);
	ShowEffect(byte* data);

	void emplace(byte* buffer) const override;
	int size() const override;
	String toString() const override;
};