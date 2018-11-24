#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "Packets/PacketWriter.h"
#include "Packets/PacketReader.h"

#include <Packets/ArenaDeath.h>

ArenaDeath::ArenaDeath(int restartPrice)
	: restartPrice(restartPrice)
{

}

ArenaDeath::ArenaDeath(byte* data)
{
	PacketReader r(data);

	r.read(restartPrice);
}

void ArenaDeath::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::ArenaDeath]);

	w.write(restartPrice);
}

int ArenaDeath::size() const
{
	return 9;
}

String ArenaDeath::toString() const
{
	return String("ARENADEATH");
}