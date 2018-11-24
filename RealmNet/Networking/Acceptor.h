#pragma once

#include "Proxy.h"
#include "Data/ServerSelection.h"

class Acceptor
{
private:
	boost::asio::io_service& ios;
	boost::asio::ip::tcp::acceptor acceptor;

	boost::asio::ip::tcp::socket* clientSock;
	boost::asio::ip::tcp::socket* serverSock;

	ServerSelection server; //TODO multiple servers

public:
	Acceptor(boost::asio::io_service& ios);

	void beginAccept();
	void acceptCallback(const boost::system::error_code& error);

	void beginConnect(const char* address);
	void connectCallback(const boost::system::error_code& error);
};