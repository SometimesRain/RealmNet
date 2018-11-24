#pragma once

#include <Packets/Packet.h>
#include <DataObjects/Array.h>
#include <DataObjects/QuestData.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API FetchQuestResponse : public ServerPacket
{
public:
	Array<QuestData> quests;

	FetchQuestResponse(const Array<QuestData>& quests);
	FetchQuestResponse(byte* data);

	void emplace(byte* buffer) const override;
	int size() const override;
	String toString() const override;
};