#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"
#include "PacketReader.h"

#include <Packets/Notification.h>

Notification::Notification(int objectId, const String& message, int color)
	: objectId(objectId), message(message), color(color)
{

}

Notification::Notification(byte* data)
{
	PacketReader r(data);

	r.read(objectId);
	r.read(message);
	r.read(color);
}

void Notification::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::Notification]);

	w.write(objectId);
	w.writeMsg(message);
	w.write(color);
}

int Notification::size() const
{
	if (message.c_str[0] != '{')
		return 51 + message.length;
	else
		return 15 + message.length;
}

String Notification::toString() const
{
	return String("NOTIFICATION");
}