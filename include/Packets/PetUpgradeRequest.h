#pragma once

#include <Packets/Packet.h>
#include <DataObjects/Array.h>
#include <DataObjects/SlotObject.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API PetUpgradeRequest : public ClientPacket
{
public:
	byte petTransType;
	int pid1;
	int pid2;
	int objectId;
	byte paymentTransType;
	Array<SlotObject> slots;

	PetUpgradeRequest(byte petTransType, int pid1, int pid2, int objectId, byte paymentTransType, const Array<SlotObject>& slots);
	PetUpgradeRequest(byte* data);

	void emplace(byte* buffer) const override;
	int size() const override;
	String toString() const override;
};