#include "stdafx.h"

#include <DataObjects/BitmapData.h>

BitmapData::BitmapData(int width, int height, const Array<byte>& data)
	: width(width), height(height), data(data)
{

}

BitmapData::BitmapData()
{

}