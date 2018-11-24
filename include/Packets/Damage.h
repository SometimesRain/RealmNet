#pragma once

#include <Packets/Packet.h>
#include <DataObjects/Array.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API Damage : public ServerPacket
{
public:
	int targetId;
	Array<byte> effects;
	int damage;
	bool kill;
	bool armorPierce;
	byte bulletId;
	int objectId;

	Damage(int targetId, const Array<byte>& effects, int damage, bool kill, bool armorPierce, byte bulletId, int objectId);
	Damage(byte* data);

	void emplace(byte* buffer) const override;
	int size() const override;
	String toString() const override;
};