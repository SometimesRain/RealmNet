#pragma once

#include <DataObjects/String.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

typedef unsigned char byte;

class PACKET_API Packet
{
public:
	virtual void emplace(byte* buffer) const = 0;
	virtual int size() const = 0;
	virtual String toString() const = 0;
};

class PACKET_API ClientPacket : public Packet
{

};

class PACKET_API ServerPacket : public Packet
{

};