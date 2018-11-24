#pragma once

#include <Packets/Packet.h>
#include <DataObjects/Array.h>
#include <DataObjects/SlotObject.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API QuestRedeem : public ClientPacket
{
public:
	String questId;
	Array<SlotObject> slots;
	int item;

	QuestRedeem(const String& questId, const Array<SlotObject>& slots, int item);
	QuestRedeem(byte* data);

	void emplace(byte* buffer) const override;
	int size() const override;
	String toString() const override;
};