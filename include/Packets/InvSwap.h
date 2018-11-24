#pragma once

#include <Packets/Packet.h>
#include <DataObjects/Location.h>
#include <DataObjects/SlotObject.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API InvSwap : public ClientPacket
{
public:
	int time;
	Location position;
	SlotObject slotObject1;
	SlotObject slotObject2;

	InvSwap(int time, const Location& position, const SlotObject& slotObject1, const SlotObject& slotObject2);
	InvSwap(int time, float x, float y, const SlotObject& slotObject1, const SlotObject& slotObject2);
	InvSwap(byte* data);

	void emplace(byte* buffer) const override;
	int size() const override;
	String toString() const override;
};