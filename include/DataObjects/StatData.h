#pragma once

#include <DataObjects/String.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API StatData
{
public:
	byte id;
	int intValue;
	String stringValue;

	StatData(byte id, const String& stringValue);
	StatData(byte id, int intValue);
	StatData();

	bool isStringValue() const;
};