#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "Packets/PacketWriter.h"
#include "Packets/PacketReader.h"

#include <Packets/GlobalNotification.h>

GlobalNotification::GlobalNotification(int type, const String& text)
	: type(type), text(text)
{

}

GlobalNotification::GlobalNotification(byte* data)
{
	PacketReader r(data);

	r.read(type);
	r.read(text);
}

void GlobalNotification::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::GlobalNotification]);

	w.write(type);
	w.write(text);
}

int GlobalNotification::size() const
{
	return 11 + text.length;
}

String GlobalNotification::toString() const
{
	return String("GLOBALNOTIFICATION");
}