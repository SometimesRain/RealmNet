#pragma once

#include "Connection.h"

class ClientConnection : public Connection
{
protected:
	void onPacket() override;

public:
	ClientConnection(Proxy* proxy, boost::asio::ip::tcp::socket* receiveSocket, boost::asio::ip::tcp::socket* sendSocket);
};