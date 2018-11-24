#pragma once

#include <Packets/Packet.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API Load : public ClientPacket
{
public:
	int charId;
	bool isFromArena;

	Load(int charId);
	Load(int charId, bool isFromArena);
	Load(byte* data);

	void emplace(byte* buffer) const override;
	int size() const override;
	String toString() const override;
};