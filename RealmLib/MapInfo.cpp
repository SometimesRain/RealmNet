#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"
#include "PacketReader.h"

#include <Packets/MapInfo.h>

MapInfo::MapInfo(byte* data)
{
	PacketReader r(data);

	r.read(width);
	r.read(height);
	r.read(name);
	r.read(displayName);
	r.read(difficulty);
	r.read(seed);
	r.read(background);
	r.read(allowTeleport);
	r.read(showDisplays);
	r.read32(clientXML);
	r.read32(extraXML);
}

void MapInfo::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::MapInfo]);

	w.write(width);
	w.write(height);
	w.write(name);
	w.write(displayName);
	w.write(difficulty);
	w.write(seed);
	w.write(background);
	w.write(allowTeleport);
	w.write(showDisplays);
	w.write32(clientXML);
	w.write32(extraXML);
}

int MapInfo::size() const
{
	int size = 35 + name.length + displayName.length;

	for (size_t i = 0; i < clientXML.length; i++)
		size += 4 + clientXML[i].length;

	for (size_t i = 0; i < extraXML.length; i++)
		size += 4 + extraXML[i].length;

	return size;
}

String MapInfo::toString() const
{
	return String("MAPINFO");
}