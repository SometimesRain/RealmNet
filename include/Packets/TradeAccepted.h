#pragma once

#include <Packets/Packet.h>
#include <DataObjects/Array.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API TradeAccepted : public ServerPacket
{
public:
	Array<bool> myOffer;
	Array<bool> yourOffer;

	TradeAccepted(const Array<bool>& myOffer, const Array<bool>& yourOffer);
	TradeAccepted(byte* data);

	void emplace(byte* buffer) const override;
	int size() const override;
	String toString() const override;
};