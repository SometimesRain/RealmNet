#pragma once

#include <Packets/Packet.h>
#include <DataObjects/Array.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API ChangeTrade : public ClientPacket
{
public:
	Array<bool> offer;

	ChangeTrade(const Array<bool>& offer);
	ChangeTrade(byte* data);

	void emplace(byte* buffer) const override;
	int size() const override;
	String toString() const override;
};