#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "Packets/PacketWriter.h"
#include "Packets/PacketReader.h"

#include <Packets/Update.h>

Update::Update(const Array<Tile>& tiles, const Array<Entity>& newObjs, const Array<int>& drops)
	: tiles(tiles), newObjs(newObjs), drops(drops)
{

}

Update::Update(byte* data)
{
	PacketReader r(data);

	r.read(tiles);
	r.read(newObjs);
	r.read(drops);
}

void Update::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::Update]);

	w.write(tiles);
	w.write(newObjs);
	w.write(drops);
}

int Update::size() const
{
	int size = 11 + 6 * tiles.length + 16 * newObjs.length + 4 * drops.length;

	for (size_t i = 0; i < newObjs.length; i++)
	{
		for (size_t j = 0; j < newObjs[i].status.data.length; j++)
		{
			StatData* data = &newObjs[i].status.data[j];
			size += data->isStringValue() ? 3 + data->stringValue.length : 5;
		}
	}

	return size;
}

String Update::toString() const
{
	return String("UPDATE");
}