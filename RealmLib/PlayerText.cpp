#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"
#include "PacketReader.h"

#include <Packets/PlayerText.h>

PlayerText::PlayerText(const String& text)
	: text(text)
{

}

PlayerText::PlayerText(byte* data)
{
	PacketReader r(data);

	r.read(text);
}

void PlayerText::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::PlayerText]);

	w.write(text);
}

int PlayerText::size() const
{
	return 7 + text.length;
}

String PlayerText::toString() const
{
	return String("PLAYERTEXT");
}