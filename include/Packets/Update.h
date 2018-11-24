#pragma once

#include <Packets/Packet.h>
#include <DataObjects/Array.h>
#include <DataObjects/Tile.h>
#include <DataObjects/Entity.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API Update : public ServerPacket
{
public:
	Array<Tile> tiles;
	Array<Entity> newObjs;
	Array<int> drops;

	Update(const Array<Tile>& tiles, const Array<Entity>& newObjs, const Array<int>& drops);
	Update(byte* data);

	void emplace(byte* buffer) const override;
	int size() const override;
	String toString() const override;
};