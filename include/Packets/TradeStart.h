#pragma once

#include <Packets/Packet.h>
#include <DataObjects/Array.h>
#include <DataObjects/TradeItem.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API TradeStart : public ServerPacket
{
public:
	Array<TradeItem> myItems;
	String yourName;
	Array<TradeItem> yourItems;

	TradeStart(const Array<TradeItem>& myItems, const String& yourName, const Array<TradeItem>& yourItems);
	TradeStart(byte* data);

	void emplace(byte* buffer) const override;
	int size() const override;
	String toString() const override;
};