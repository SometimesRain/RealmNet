#pragma once

#include <DataObjects/Array.h>
#include <DataObjects/Location.h>
#include <DataObjects/StatData.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API Status
{
public:
	int objectId;
	Location position;
	Array<StatData> data;

	Status(int objectId, const Location& position, const Array<StatData>& data);
	Status();
};