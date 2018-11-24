#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"
#include "PacketReader.h"

#include <Packets/FetchQuestResponse.h>

FetchQuestResponse::FetchQuestResponse(const Array<QuestData>& quests)
	: quests(quests)
{

}

FetchQuestResponse::FetchQuestResponse(byte* data)
{
	PacketReader r(data);

	r.read(quests);
}

void FetchQuestResponse::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::FetchQuestResponse]);

	w.write(quests);
}

int FetchQuestResponse::size() const
{
	int size = 7 + 16 * quests.length;

	for (size_t i = 0; i < quests.length; i++)
		size += quests[i].id.length + quests[i].name.length + quests[i].description.length + 4 * quests[i].requirements.length + 4 * quests[i].rewards.length;

	return size;
}

String FetchQuestResponse::toString() const
{
	return String("FETCHQUESTRESPONSE");
}