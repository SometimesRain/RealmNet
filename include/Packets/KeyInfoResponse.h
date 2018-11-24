#pragma once

#include <Packets/Packet.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API KeyInfoResponse : public ServerPacket
{
public:
	String name;
	String description;
	String creator;

	KeyInfoResponse(const String& name, const String& description, const String& creator);
	KeyInfoResponse(byte* data);

	void emplace(byte* buffer) const override;
	int size() const override;
	String toString() const override;
};