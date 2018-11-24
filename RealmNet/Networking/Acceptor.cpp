#include "stdafx.h"

#include "Acceptor.h"
#include "Data/SettingsFile.h"

//an Acceptor class that creates Proxy instance for each connection

Acceptor::Acceptor(boost::asio::io_service& ios)
	: ios(ios), acceptor(ios, boost::asio::ip::tcp::endpoint(boost::asio::ip::address_v4::loopback(), 2050)),
	server(SettingsFile::settings.defaultHost)
{
	beginAccept();
}

void Acceptor::beginAccept()
{
	clientSock = new boost::asio::ip::tcp::socket(ios);
	acceptor.async_accept(*clientSock, boost::bind(&Acceptor::acceptCallback, this, boost::asio::placeholders::error));
}

void Acceptor::acceptCallback(const boost::system::error_code& error)
{
	if (!error)
	{
		printf("Connecting to %s\n", server.currentHost.c_str);
		beginConnect(server.currentHost.c_str); //TODO multiple servers
	}
	else
	{
		printf("acceptCallback(): %s\n", error.message().c_str());
	}
}

void Acceptor::beginConnect(const char* address)
{
	serverSock = new boost::asio::ip::tcp::socket(ios);
	serverSock->async_connect(
		boost::asio::ip::tcp::endpoint(boost::asio::ip::address_v4::from_string(address), 2050),
		boost::bind(&Acceptor::connectCallback, this, boost::asio::placeholders::error)
	);
}

void Acceptor::connectCallback(const boost::system::error_code& error)
{
	//puts("Connected");
	if (!error)
	{
		new Proxy(server, clientSock, serverSock); //will delete itself
		beginAccept();
	}
	else
	{
		printf("connectCallback(): %s\n", error.message().c_str());
	}
}