#pragma once

#include <Packets/Packet.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API Text : public ServerPacket
{
public:
	String name;
	int objectId;
	int numStars;
	byte bubbleTime;
	String recipient;
	String text;
	String cleanText;
	bool isSupporter;

	Text(const String& name, const String& text);
	Text(const String& name, int objectId, int numStars, const String& recipient, const String& text);
	Text(const String& name, int objectId, int numStars, const String& recipient, const String& text, bool isSupporter);
	Text(byte* data);

	void emplace(byte* buffer) const override;
	int size() const override;
	String toString() const override;
};