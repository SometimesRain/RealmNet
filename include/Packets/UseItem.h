#pragma once

#include <Packets/Packet.h>
#include <DataObjects/SlotObject.h>
#include <DataObjects/Location.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API UseItem : public ClientPacket
{
public:
	int time;
	SlotObject slotObject;
	Location position;
	byte useType;

	UseItem(int time, const SlotObject& slotObject, const Location& position, byte useType);
	UseItem(int time, const SlotObject& slotObject, float x, float y, byte useType);
	UseItem(byte* data);

	void emplace(byte* buffer) const override;
	int size() const override;
	String toString() const override;
};