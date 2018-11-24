#pragma once

#include "Connection.h"
#include <DataObjects/StatData.h>
#include <DataObjects/Array.h>

class ServerConnection : public Connection
{
private:
	void updateStatData(const Array<StatData>& data);

protected:
	void onPacket() override;

public:
	ServerConnection(Proxy* proxy, boost::asio::ip::tcp::socket* receiveSocket, boost::asio::ip::tcp::socket* sendSocket);

	void closeSocket();
};