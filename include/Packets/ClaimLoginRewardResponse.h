#pragma once

#include <Packets/Packet.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API ClaimLoginRewardResponse : public ServerPacket
{
public:
	int itemId;
	int quantity;
	int gold;

	ClaimLoginRewardResponse(int itemId, int quantity, int gold);
	ClaimLoginRewardResponse(byte* data);

	void emplace(byte* buffer) const override;
	int size() const override;
	String toString() const override;
};