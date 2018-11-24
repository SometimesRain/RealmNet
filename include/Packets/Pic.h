#pragma once

#include <Packets/Packet.h>
#include <DataObjects/BitmapData.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API Pic : public ServerPacket
{
public:
	BitmapData bitmapData;

	Pic(const BitmapData& bitmapData);
	Pic(byte* data);

	void emplace(byte* buffer) const override;
	int size() const override;
	String toString() const override;
};