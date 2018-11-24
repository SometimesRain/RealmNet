#include "stdafx.h"

#include "Proxy.h"
#include "Data/PluginManager.h"

//each Proxy has their own instances of the Plugins and Connections to the server and the client

Proxy::Proxy(ServerSelection& server, boost::asio::ip::tcp::socket* clientSock, boost::asio::ip::tcp::socket* serverSock)
	: clientConn(this, clientSock, serverSock), serverConn(this, serverSock, clientSock), server(server)
{
	clientConn.beginRead(boost::system::error_code());
	serverConn.beginRead(boost::system::error_code());

	//instantiate plugins
	size_t size = PluginManager::instantiators.size();
	plugins = new IPlugin*[size];
	for (size_t i = 0; i < size; i++)
		plugins[i] = PluginManager::instantiators[i](*this);
	KeyHook::add(this);
}

Proxy::~Proxy()
{
	for (size_t i = 0; i < PluginManager::instantiators.size(); i++)
	{
		if (PluginManager::disconnectCallbacks[i])
			(*plugins[i].*PluginManager::disconnectCallbacks[i])();
		delete plugins[i];
	}
	delete[] plugins;
}

void Proxy::hookPacket(byte packetType, IPlugin* instance, void(IPlugin::*callback)(Packet&))
{
	callbacks[packetType].push_back(CallbackFunc<Packet&>(instance, callback));
}

void Proxy::hookCommand(const char* command, IPlugin* instance, void(IPlugin::*callback)(int, const char**))
{
	commandCallbacks.push_back(std::make_pair(command, CallbackFunc<int, const char**>(instance, callback)));
}

int Proxy::getTime()
{
	return previousTime + std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - lastUpdate).count();
}

void Proxy::sendPacket(const ServerPacket& packet)
{
	serverConn.sendPacket(packet);
}

void Proxy::sendPacket(const ClientPacket& packet)
{
	clientConn.sendPacket(packet);
}

void Proxy::updatePacket(ServerPacket& packet)
{
	serverConn.updatePacket(packet);
}

void Proxy::updatePacket(ClientPacket& packet)
{
	clientConn.updatePacket(packet);
}

void Proxy::discardPacket(ServerPacket& packet)
{
	serverConn.discardPacket(packet);
}

void Proxy::discardPacket(ClientPacket& packet)
{
	clientConn.discardPacket(packet);
}

void Proxy::disconnect()
{
	//immediately close the server socket and let the Connection fail -> Proxy gets closed down
	serverConn.closeSocket();
}