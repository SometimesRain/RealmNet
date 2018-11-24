#pragma once

#include <Packets/Packet.h>
#include <DataObjects/PlayerData.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class IPlugin;

class PACKET_API IProxy
{
public:
	PlayerData playerData;

	virtual void hookPacket(byte packetType, IPlugin* instance, void(IPlugin::*callback)(Packet&)) = 0;
	virtual void hookCommand(const char* command, IPlugin* instance, void(IPlugin::*callback)(int, const char**)) = 0;

	virtual int getTime() = 0;

	virtual void sendPacket(const ServerPacket& packet) = 0;
	virtual void sendPacket(const ClientPacket& packet) = 0;
	virtual void updatePacket(ServerPacket& packet) = 0;
	virtual void updatePacket(ClientPacket& packet) = 0;
	virtual void discardPacket(ServerPacket& packet) = 0;
	virtual void discardPacket(ClientPacket& packet) = 0;

	virtual void disconnect() = 0;
};

class PACKET_API IPlugin
{
public:
	IProxy& proxy;

	IPlugin(IProxy& proxy) : proxy(proxy)
	{

	}
};

class PACKET_API HookedKey
{
public:
	byte vkKey;
	byte modifier;
	bool global;
	void(IPlugin::*callback)(bool);

	HookedKey(byte vkKey, byte modifier, bool global, void(IPlugin::*callback)(bool));
};

#ifdef PLUGIN
extern "C"
{
	__declspec(dllexport) IPlugin* create(IProxy& proxy);
	__declspec(dllexport) void attach(const char** plugin, const char** author, void(IPlugin::**onDisconnect)(), HookedKey** keyHook);
}

#define HookPacket(type) proxy.hookPacket(PacketType::##type, this, (void(IPlugin::*)(Packet&))&Plugin::on##type)
#define HookCommand(command, callback) proxy.hookCommand(command, this, (void(IPlugin::*)(int, const char**))&Plugin::callback)
#define HookKey(vkCode, modifier, global, callback) *keyHook++ = new HookedKey(Key::vkCode, Modifier::modifier, global, (void(IPlugin::*)(bool))&Plugin::callback)
#define LinkDisconnectCallback() *onDisconnect = (void(IPlugin::*)())&Plugin::onDisconnect;
#endif