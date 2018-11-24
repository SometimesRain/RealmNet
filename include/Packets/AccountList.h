#pragma once

#include <Packets/Packet.h>
#include <DataObjects/Array.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API AccountList : public ServerPacket
{
public:
	int accountListId;
	Array<String> accountIds;
	int lockAction;

	AccountList(int accountListId, const Array<String>& accountIds, int lockAction);
	AccountList(byte* data);

	void emplace(byte* buffer) const override;
	int size() const override;
	String toString() const override;
};