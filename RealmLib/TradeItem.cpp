#include "stdafx.h"

#include <DataObjects/TradeItem.h>

TradeItem::TradeItem(int item, int slotType, bool tradable, bool included)
	: item(item), slotType(slotType), tradable(tradable), included(included)
{

}

TradeItem::TradeItem()
{

}