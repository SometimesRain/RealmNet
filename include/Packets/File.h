#pragma once

#include <Packets/Packet.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API File : public ServerPacket
{
public:
	String filename;
	String contents;

	File(const String& filename, const String& contents);
	File(byte* data);

	void emplace(byte* buffer) const override;
	int size() const override;
	String toString() const override;
};