#pragma once

#include <Packets/Packet.h>
#include <DataObjects/Array.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API TradeChanged : public ServerPacket
{
public:
	Array<bool> offer;

	TradeChanged(const Array<bool>& offer);
	TradeChanged(byte* data);

	void emplace(byte* buffer) const override;
	int size() const override;
	String toString() const override;
};