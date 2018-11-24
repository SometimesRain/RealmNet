#pragma once

#include <Packets/Packet.h>
#include <DataObjects/SlotObject.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API ReskinPet : public ClientPacket
{
public:
	int instanceId;
	int newPetType;
	SlotObject item;

	ReskinPet(int instanceId, int newPetType, const SlotObject& item);
	ReskinPet(byte* data);

	void emplace(byte* buffer) const override;
	int size() const override;
	String toString() const override;
};