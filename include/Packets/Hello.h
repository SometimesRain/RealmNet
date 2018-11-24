#pragma once

#include <Packets/Packet.h>
#include <DataObjects/Array.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API Hello : public ClientPacket
{
public:
	String buildVersion;
	int gameId;
	String guid;
	int random1;
	String password;
	int random2;
	String secret;
	int keyTime;
	Array<byte> key;
	String mapJSON;
	String entryTag;
	String gameNet;
	String gameNetUserId;
	String playPlatform;
	String platformToken;
	String userToken;

	Hello(const String& buildVersion, const String& guid, const String& password, int gameId, int keyTime, const Array<byte>& key);
	Hello(const String& buildVersion, const String& guid, const String& password, int gameId);
	Hello(byte* data);

	void emplace(byte* buffer) const override;
	int size() const override;
	String toString() const override;
};