#include "stdafx.h"

#include <DataObjects/StatData.h>

StatData::StatData(byte id, const String& stringValue)
	: id(id), stringValue(stringValue)
{

}

StatData::StatData(byte id, int intValue)
	: id(id), intValue(intValue)
{

}

StatData::StatData()
{

}

bool StatData::isStringValue() const //TODO more proper implementation
{
	return id == 31 || id == 62 || id == 82 || id == 38 || id == 54;
}