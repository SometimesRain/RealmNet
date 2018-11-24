#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"
#include "PacketReader.h"

#include <Packets/NewTick.h>

NewTick::NewTick(int tickId, int tickTime, const Array<Status>& statuses)
	: tickId(tickId), tickTime(tickTime), statuses(statuses)
{

}

NewTick::NewTick(byte* data)
{
	PacketReader r(data);

	r.read(tickId);
	r.read(tickTime);
	r.read(statuses);
}

void NewTick::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::NewTick]);

	w.write(tickId);
	w.write(tickTime);
	w.write(statuses);
}

int NewTick::size() const
{
	int size = 15 + 14 * statuses.length;

	for (size_t i = 0; i < statuses.length; i++)
	{
		for (size_t j = 0; j < statuses[i].data.length; j++)
		{
			StatData* data = &statuses[i].data[j];
			size += data->isStringValue() ? 3 + data->stringValue.length : 5;
		}
	}

	return size;
}

String NewTick::toString() const
{
	return String("NEWTICK");
}