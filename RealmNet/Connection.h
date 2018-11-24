#pragma once

#include "RC4Cipher.h"
#include <Packets/Packet.h>
#include <boost/asio.hpp>

class Proxy;

class Connection
{
private:
	bool connectionTerminated();

protected:
	Proxy& proxy;
	boost::asio::ip::tcp::socket* receiveSocket;
	boost::asio::ip::tcp::socket* sendSocket;
	RC4Cipher incomingCipher;
	RC4Cipher outgoingCipher;

	enum { receiveDoubleSize = 262144, receiveSize = 131072, sendSize = 1024 };
	byte receiveBuffer[receiveDoubleSize];
	byte* receiveBuffer2 = receiveBuffer + receiveSize;
	byte* receivePtr = receiveBuffer2;
	byte sendBuffer[sendSize];

	int addBytes = 0;
	int dataAmount = 0;
	int head = 0;
	int headAccumulate = 0;

	bool receiving = false;
	bool discard = false;
	byte packetType;

	virtual void onPacket() = 0;

public:
	Connection(Proxy* proxy, boost::asio::ip::tcp::socket* receiveSocket, boost::asio::ip::tcp::socket* sendSocket, const byte* key);

	void disconnect();

	void beginRead(const boost::system::error_code& error);
	void readCallback(const boost::system::error_code& error, const size_t& bytes_transferred);

	void sendPacket(const Packet& packet);
	void sendPacketCallback(const boost::system::error_code& error);

	void updatePacket(Packet& packet);
	void discardPacket(Packet& packet);
	void fireCallbacks(Packet& packet);
};