#pragma once

#include <Packets/Packet.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API ChangePetSkin : public ClientPacket
{
public:
	int petId;
	int skinType;
	int currency;

	ChangePetSkin(int petId, int skinType, int currency);
	ChangePetSkin(byte* data);

	void emplace(byte* buffer) const override;
	int size() const override;
	String toString() const override;
};