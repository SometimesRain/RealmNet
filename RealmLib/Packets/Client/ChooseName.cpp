#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "Packets/PacketWriter.h"
#include "Packets/PacketReader.h"

#include <Packets/ChooseName.h>

ChooseName::ChooseName(const String& name)
	: name(name)
{

}

ChooseName::ChooseName(byte* data)
{
	PacketReader r(data);

	r.read(name);
}

void ChooseName::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::ChooseName]);

	w.write(name);
}

int ChooseName::size() const
{
	return 7 + name.length;
}

String ChooseName::toString() const
{
	return String("CHOOSENAME");
}