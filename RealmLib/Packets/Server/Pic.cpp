#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "Packets/PacketWriter.h"
#include "Packets/PacketReader.h"

#include <Packets/Pic.h>

Pic::Pic(const BitmapData& bitmapData)
	: bitmapData(bitmapData)
{

}

Pic::Pic(byte* data)
{
	PacketReader r(data);

	r.read(bitmapData);
}

void Pic::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::Pic]);

	w.write(bitmapData);
}

int Pic::size() const
{
	return 8 + bitmapData.width * bitmapData.height * 4;
}

String Pic::toString() const
{
	return String("PIC");
}