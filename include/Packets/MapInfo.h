#pragma once

#include <Packets/Packet.h>
#include <DataObjects/Array.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API MapInfo : public ServerPacket
{
public:
	int width;
	int height;
	String name;
	String displayName;
	int difficulty;
	uint seed;
	int background;
	bool allowTeleport;
	bool showDisplays;
	Array<String> clientXML;
	Array<String> extraXML;

	MapInfo(byte* data);

	void emplace(byte* buffer) const override;
	int size() const override;
	String toString() const override;
};