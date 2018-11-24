#pragma once

#include <Packets/Packet.h>
#include <DataObjects/Location.h>
#include <DataObjects/Array.h>
#include <DataObjects/MoveRecord.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API Move : public ClientPacket
{
public:
	int tickId;
	int time;
	Location newPosition;
	Array<MoveRecord> records;

	Move(int tickId, int time, const Location& newPosition);
	Move(int tickId, int time, const Location& newPosition, const Array<MoveRecord>& records);
	Move(byte* data);

	void emplace(byte* buffer) const override;
	int size() const override;
	String toString() const override;
};