#pragma once

#include <Packets/Packet.h>
#include <DataObjects/Array.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API AcceptTrade : public ClientPacket
{
public:
	Array<bool> myOffer;
	Array<bool> yourOffer;

	AcceptTrade(const Array<bool>& myOffer, const Array<bool>& yourOffer);
	AcceptTrade(byte* data);

	void emplace(byte* buffer) const override;
	int size() const override;
	String toString() const override;
};