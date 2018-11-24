#pragma once

#include <DataObjects/Status.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API Entity
{
public:
	ushort objectType;
	Status status;

	Entity(ushort objectType, const Status& status);
	Entity();
};