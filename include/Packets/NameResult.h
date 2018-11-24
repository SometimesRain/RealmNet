#pragma once

#include <Packets/Packet.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API NameResult : public ServerPacket
{
public:
	bool success;
	String errorMessage;

	NameResult(bool success, const String& errorMessage);
	NameResult(byte* data);

	void emplace(byte* buffer) const override;
	int size() const override;
	String toString() const override;
};