#include "stdafx.h"

#include <Packets/CreateSuccess.h>
#include <Packets/Notification.h>

class Plugin : public IPlugin
{
public:
	Plugin(IProxy& proxy) : IPlugin(proxy)
	{
		HookPacket(CreateSuccess);
	}

	void onCreateSuccess(CreateSuccess& p)
	{
		proxy.sendPacket(Notification(proxy.playerData.objectId, "Welcome to RealmNet!", 0x00ff80));
	}
};

IPlugin* create(IProxy& proxy)
{
	return new Plugin(proxy);
}

void attach(const char** plugin, const char** author, void(IPlugin::**onDisconnect)(), HookedKey** keyHook)
{
	*plugin = "Welcome";
	*author = "CrazyJani";
}