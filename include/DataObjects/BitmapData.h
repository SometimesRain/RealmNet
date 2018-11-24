#pragma once

#include <DataObjects/Array.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API BitmapData
{
public:
	int width;
	int height;
	Array<byte> data;

	BitmapData(int width, int height, const Array<byte>& data);
	BitmapData();
};