#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "Packets/PacketWriter.h"
#include "Packets/PacketReader.h"

#include <Packets/Text.h>

Text::Text(const String& name, const String& text)
	: name(name), objectId(-1), numStars(-1), text(text), bubbleTime(10), isSupporter(false)
{

}

Text::Text(const String& name, int objectId, int numStars, const String& recipient, const String& text)
	: name(name), objectId(objectId), numStars(numStars), recipient(recipient), text(text), bubbleTime(10), isSupporter(false)
{

}

Text::Text(const String& name, int objectId, int numStars, const String& recipient, const String& text, bool isSupporter)
	: name(name), objectId(objectId), numStars(numStars), recipient(recipient), text(text), bubbleTime(10), isSupporter(isSupporter)
{

}

Text::Text(byte* data)
{
	PacketReader r(data);

	r.read(name);
	r.read(objectId);
	r.read(numStars);
	r.read(bubbleTime);
	r.read(recipient);
	r.read(text);
	r.read(cleanText);
	r.read(isSupporter);
}

void Text::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::Text]);

	w.write(name);
	w.write(objectId);
	w.write(numStars);
	w.write(bubbleTime);
	w.write(recipient);
	w.write(text);
	w.write(cleanText);
	w.write(isSupporter);
}

int Text::size() const
{
	return 22 + name.length + recipient.length + text.length + cleanText.length;
}

String Text::toString() const
{
	return String("TEXT");
}