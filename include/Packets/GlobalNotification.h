#pragma once

#include <Packets/Packet.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API GlobalNotification : public ServerPacket
{
public:
	int type;
	String text;

	GlobalNotification(int type, const String& text);
	GlobalNotification(byte* data);

	void emplace(byte* buffer) const override;
	int size() const override;
	String toString() const override;
};