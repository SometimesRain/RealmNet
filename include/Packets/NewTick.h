#pragma once

#include <Packets/Packet.h>
#include <DataObjects/Array.h>
#include <DataObjects/Status.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API NewTick : public ServerPacket
{
public:
	int tickId;
	int tickTime;
	Array<Status> statuses;

	NewTick(int tickId, int tickTime, const Array<Status>& statuses);
	NewTick(byte* data);

	void emplace(byte* buffer) const override;
	int size() const override;
	String toString() const override;
};