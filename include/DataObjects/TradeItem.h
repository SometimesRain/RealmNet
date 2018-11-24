#pragma once

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API TradeItem
{
public:
	int item;
	int slotType;
	bool tradable;
	bool included;

	TradeItem(int item, int slotType, bool tradable, bool included);
	TradeItem();
};