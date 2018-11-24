#include "stdafx.h"

#include "Proxy.h"
#include <GameData/TypeManager.h>
#include <Packets/Reconnect.h>

inline void extract32(byte* buffer, int& val);
inline void printPacket(byte* buffer, size_t size);

Connection::Connection(Proxy* proxy, boost::asio::ip::tcp::socket* receiveSocket, boost::asio::ip::tcp::socket* sendSocket, const byte* key)
	: proxy(*proxy), receiveSocket(receiveSocket), sendSocket(sendSocket), incomingCipher(key), outgoingCipher(key)
{

}

void Connection::disconnect() //calling this twice will crash the program
{
	KeyHook::remove(&proxy);
	puts("Disconnected");

	if (receiveSocket->is_open())
		receiveSocket->close();

	if (sendSocket->is_open())
		sendSocket->close();

	delete receiveSocket;
	delete sendSocket;
	delete &proxy;
}

void Connection::beginRead(const boost::system::error_code& error)
{
	if (!error)
	{
		receivePtr = receiveBuffer2 - (receivePtr - receiveBuffer); //swap buffers
		receiveSocket->async_read_some(
			boost::asio::buffer(receivePtr + dataAmount, receiveSize - dataAmount),
			boost::bind(&Connection::readCallback, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)
		);
	}
	else
	{
		if (error.value() != 10054)
			printf("beginRead() %d: %s\n", error.value(), error.message().c_str());
		disconnect();
	}
}

bool Connection::connectionTerminated()
{
	if (headAccumulate == dataAmount - 1) //0xff in the buffer
	{
		disconnect();
		return true;
	}
	return false;
}

void Connection::readCallback(const boost::system::error_code& error, const size_t& bytes_transferred)
{
	if (!error)
	{
		receiving = true;
		dataAmount += bytes_transferred;
		headAccumulate = 0;

		while (true) //loop through all received packets
		{
			if (connectionTerminated()) return;

			extract32(receivePtr + headAccumulate, head);

			if (headAccumulate + head <= dataAmount) //a new packet has to be parsed
			{
				incomingCipher.cipher(receivePtr + headAccumulate + 5, head - 5);
				packetType = TypeManager::idToType[receivePtr[headAccumulate + 4]];

				onPacket();

				if (discard)
					discard = false;
				else
					outgoingCipher.cipher(receivePtr + headAccumulate + 5, head - 5);

				headAccumulate += head;

				if (headAccumulate == dataAmount) //all packets have been read
					break;
			}
			else //there is a partial packet
			{
				//copy the partial packet to the beginning of the flip buffer (moveAmount = dataAmount - headAccumulate)
				memcpy(receiveBuffer2 - (receivePtr - receiveBuffer), receivePtr + headAccumulate, dataAmount - headAccumulate);
				//seal the hole left by the incomplete packet
				memmove(receivePtr + headAccumulate, receivePtr + dataAmount, addBytes);
				break;
			}
		}

		receiving = false;
		dataAmount -= headAccumulate; //headAccumulate has the amount of data that was forwarded
		if (addBytes)
		{
			addBytes += headAccumulate + dataAmount;

			while (true) //loop through all added packets and cipher them
			{
				extract32(receivePtr + headAccumulate, head);

				if (headAccumulate + head <= addBytes)
				{
					outgoingCipher.cipher(receivePtr + headAccumulate + 5, head - 5);

					headAccumulate += head;

					if (headAccumulate == addBytes) //all packets have been added
					{
						addBytes = 0;
						break;
					}
				}
				else
					break;
			}
		}

		async_write(*sendSocket,
			boost::asio::buffer(receivePtr, headAccumulate),
			boost::bind(&Connection::beginRead, this, boost::asio::placeholders::error)
		);
	}
	else
	{
		if (error.value() != 1236)
		{
			if (error.value() != 2 && error.value() != 10054)
				printf("readCallback() %d: %s\n", error.value(), error.message().c_str());
			disconnect();
		}
	}
}

//ServerConnection: ServerPacket to client
//ClientConnection: ClientPacket to server
void Connection::sendPacket(const Packet& packet)
{
	int size = packet.size();

	if (receiving) //when receiving -> store packets at the back of the buffer
	{
		packet.emplace(receivePtr + dataAmount + addBytes);
		addBytes += packet.size();
	}
	else //when NOT receiving -> do an async send on the sendsocket
	{
		packet.emplace(sendBuffer);
		outgoingCipher.cipher(sendBuffer + 5, size - 5);

		async_write(*sendSocket,
			boost::asio::buffer(sendBuffer, size),
			boost::bind(&Connection::sendPacketCallback, this, boost::asio::placeholders::error)
		);
	}
}

void Connection::sendPacketCallback(const boost::system::error_code& error)
{
	if (error)
	{
		printf("sendPacketCallback() %d: %s\n", error.value(), error.message().c_str());
	}
}

void Connection::updatePacket(Packet& packet)
{
	int size = packet.size();
	if (size != head)
		memmove(receivePtr + headAccumulate + size, receivePtr + headAccumulate + head, dataAmount - headAccumulate - head); //move the old data in the buffer
	packet.emplace(receivePtr + headAccumulate); //place the data
	dataAmount += size - head;
	head = size;
}

void Connection::discardPacket(Packet& packet)
{
	memmove(receivePtr + headAccumulate, receivePtr + headAccumulate + head, dataAmount - headAccumulate - head);
	headAccumulate -= head;
	dataAmount -= head;
	discard = true;
}

void Connection::fireCallbacks(Packet& packet)
{
	for (auto& callback : proxy.callbacks[packetType])
	{
		if (discard)
			break;
		callback(packet);
	}
}

inline void extract32(byte* buffer, int& val)
{
	byte* ptr = (byte*)&val;
	ptr[3] = buffer[0];
	ptr[2] = buffer[1];
	ptr[1] = buffer[2];
	ptr[0] = buffer[3];
}

inline void printPacket(byte* buffer, size_t size)
{
	for (size_t i = 1; i <= size; i++)
	{
		printf("%02x ", buffer[i-1]);
		if (i % 32 == 0 || i == size)
			printf("\n");
	}
}