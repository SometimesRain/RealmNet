#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "Packets/PacketWriter.h"
#include "Packets/PacketReader.h"

#include <Packets/QuestRedeem.h>

QuestRedeem::QuestRedeem(const String& questId, const Array<SlotObject>& slots, int item)
	: questId(questId), slots(slots), item(item)
{

}

QuestRedeem::QuestRedeem(byte* data)
{
	PacketReader r(data);

	r.read(questId);
	r.read(slots);
	r.read(item);
}

void QuestRedeem::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::QuestRedeem]);

	w.write(questId);
	w.write(slots);
	w.write(item);
}

int QuestRedeem::size() const
{
	return 13 + questId.length + 9 * slots.length;
}

String QuestRedeem::toString() const
{
	return String("QUESTREDEEM");
}