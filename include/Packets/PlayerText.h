#pragma once

#include <Packets/Packet.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API PlayerText : public ClientPacket
{
public:
	String text;

	PlayerText(const String& text);
	PlayerText(byte* data);

	void emplace(byte* buffer) const override;
	int size() const override;
	String toString() const override;
};