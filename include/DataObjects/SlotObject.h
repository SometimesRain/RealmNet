#pragma once

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API SlotObject
{
public:
	int objectId;
	byte slotId;
	int objectType;

	SlotObject(int objectId, byte slotId, int objectType);
	SlotObject();
};