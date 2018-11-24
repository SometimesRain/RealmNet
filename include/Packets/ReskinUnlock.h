#pragma once

#include <Packets/Packet.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API ReskinUnlock : public ServerPacket
{
public:
	int skinId;
	int isPetSkin;

	ReskinUnlock(int skinId, int isPetSkin);
	ReskinUnlock(byte* data);

	void emplace(byte* buffer) const override;
	int size() const override;
	String toString() const override;
};