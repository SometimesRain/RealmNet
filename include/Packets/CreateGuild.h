#pragma once

#include <Packets/Packet.h>
#include <DataObjects/String.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API CreateGuild : public ClientPacket
{
public:
	String name;

	CreateGuild(const String& name);
	CreateGuild(byte* data);

	void emplace(byte* buffer) const override;
	int size() const override;
	String toString() const override;
};