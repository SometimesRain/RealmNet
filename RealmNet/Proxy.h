#pragma once

#include <Interface/IPlugin.h>
#include "ClientConnection.h"
#include "ServerConnection.h"
#include "CallbackFunc.h"
#include "ServerSelection.h"
#include "KeyHook.h"

class Proxy : public IProxy
{
private:
	ClientConnection clientConn;
	ServerConnection serverConn;

public:
	std::vector<CallbackFunc<Packet&>> callbacks[255];
	std::vector<std::pair<const char*, CallbackFunc<int, const char**>>> commandCallbacks;

	IPlugin** plugins;
	ServerSelection& server;

	int previousTime;
	std::chrono::time_point<std::chrono::steady_clock> lastUpdate;

	Proxy(ServerSelection& server, boost::asio::ip::tcp::socket* clientSock, boost::asio::ip::tcp::socket* serverSock);
	~Proxy();

	void hookPacket(byte packetType, IPlugin* instance, void(IPlugin::*callback)(Packet&)) override;
	void hookCommand(const char* command, IPlugin* instance, void(IPlugin::*callback)(int, const char**)) override;

	int getTime() override;

	void sendPacket(const ServerPacket& packet) override;
	void sendPacket(const ClientPacket& packet) override;
	void updatePacket(ServerPacket& packet) override;
	void updatePacket(ClientPacket& packet) override;
	void discardPacket(ServerPacket& packet) override;
	void discardPacket(ClientPacket& packet) override;

	void disconnect() override;
};