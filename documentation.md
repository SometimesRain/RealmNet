# RealmNet Plugin Documentation

## Plugin structure

Each plugin consists of three parts:

1. A class that inherits from **IPlugin**, containing the actual implementation of the plugin.

2. Function `create` which is called every time the proxy connects to a new game instance.

3. Function `attach` which is called once when the program starts.

A simple plugin for showing a Notification when sending a message:

```C++
#include "stdafx.h"

#include <Packets/PlayerText.h>
#include <Packets/Notification.h>

class Plugin : public IPlugin
{
public:
    Plugin(IProxy& proxy) : IPlugin(proxy)
    {
        //hook all packets here
        HookPacket(PlayerText);
    }

    void onPlayerText(PlayerText& p)
    {
        proxy.sendPacket(Notification(proxy.playerData.objectId, p.text, 0x00ff80));
    }
};

IPlugin* create(IProxy& proxy)
{
    return new Plugin(proxy);
}

void attach(const char** plugin, const char** author, void(IPlugin::**onDisconnect)(), HookedKey** keyHook)
{
    *plugin = "Plugin";
    *author = "Author";
}
```

## IProxy interface

Every plugin class has access to an **IProxy** interface which is used to perform operations on packets and for accessing hooks. It also serves as a way to access certain data regarding the current connection.

#### Hooks

Hooking is done by calling the macros `HookPacket(type)` for packets, or `HookCommand(command, callback)` for commands. Once hooked the callback function is called every time a packet of the desired type is received (or the command is intercepted).

An example packet and command hook callback:

```C++
void onPlayerText(PlayerText& p);
void onCommand(int argc, const char** argv);
```

Hooking packets and commands is done on the **Plugin**'s constructor. Hooking keys and a disconnect callback can be done with the macros `HookKey(key, modifier, global, callback)` and `LinkDisconnectCallback()`. A keyhook takes four arguments; the key to be hooked, a modifier (Shift, Control, None, etc.), a boolean and a callback function. The `global` boolean specifies whether the callback should be called on the client with most recent activity or all the clients (`true` for latter). The callback function takes one argument that contains the information whether the key was pressed down or released.

An example keyhook and disconnect callback:

```C++
void onKey(bool down);
void onDisconnect();
```
    
#### Packet operations

A plugin can send, discard and update packets. The implementation differs quite a bit from **K Relay**'s way of doing things. Comparisons between the two will help illustrate the point.

| Action  | RealmNet                                                                                                 | K Relay                                                                                                                         |
|---------|----------------------------------------------------------------------------------------------------------|---------------------------------------------------------------------------------------------------------------------------------|
| Send    | Call the `proxy.sendPacket(packet)` function. The direction of the packet is automatically determined. | Call either `proxy.sendToClient(packet)` or `proxy.sendToServer(packet)` depending on whether it's a server or a client packet. |
| Discard | Call the `proxy.discardPacket(packet)` function.                                                       | Set the `packet.send` property to `false`.                                                                                        |
| Update  | Call the `proxy.updatePacket(packet)` function.                                                        | Do nothing. Packets are updated automatically.                                                                                  |

#### Miscellaneous

Access to **PlayerData** is gained through the `proxy.playerData` variable. It contains all the information about the player. If you need to know the player's objectId or their inventory this is where you'll find it. Sometimes you also need to know the client time. This can be accessed with the function `proxy.getTime()`. A plugin can also call `proxy.disconnect()` to end the connection immediately.

Example of sending a **UseItem** packet to the server (accesses time and PlayerData):

```C++
proxy.sendPacket(UseItem(proxy.getTime(),
    SlotObject(proxy.playerData.objectId, 1, proxy.playerData.inventory[1]),
    proxy.playerData.position, 1));
```

## Plugin instances and data

Every connection has a separate instance of each of the plugins. This means that a player connected to proxy, standing in Nexus has an instance of all the attached plugins. When he enters the Vault portal, all the plugin instances are destructed and new instances created. Similarly, two clients connected to the proxy at once have separate instances of the plugins.

This has a few implications we'll start to explore now with an earlier version of the **Welcome** plugin included in RealmNet:

```C++
class Plugin : public IPlugin
{
private:
    bool welcomed = false;

public:
    Plugin(IProxy& proxy) : IPlugin(proxy)
    {
        HookPacket(Update);
    }

    void onUpdate(Update& p)
    {
        if (!welcomed)
        {
            welcomed = true;
            proxy.sendPacket(Notification(proxy.playerData.objectId, "Welcome to RealmNet!", 0x00ff80));
        }
    }
};
```

Every time a new connection is made, a new `bool welcomed` is initialized to `false`. The onUpdate method sets it to `true` as soon as the player enters the world. In this configuration, the player is greeted with a welcome message **every time the map changes**.

However if we move the variable out of the class, the behavior changes:

```C++
bool welcomed = false;

class Plugin : public IPlugin
{
public:
    Plugin(IProxy& proxy) : IPlugin(proxy)
    {
        HookPacket(Update);
    }

    void onUpdate(Update& p)
    {
        if (!welcomed)
        {
            welcomed = true;
            proxy.sendPacket(Notification(proxy.playerData.objectId, "Welcome to RealmNet!", 0x00ff80));
        }
    }
};
```

This creates the variable `bool welcomed` when the plugin is attached to the proxy which happens only once. Now the player is greeted **only on the first time** they enter Nexus.

Out-of-the-class variables can also be used to pass data between connected clients and in situations where repeating an action for every connection doesn't make sense (e.g. reading a settings file).

## XML data

XML Data can be accessed by including the header `<GameData/XmlData.h>`. The **XmlData** namespace provides access to the following functions:

```C++
ItemData* typeToItem(int type);
ObjectData* typeToObject(int type);
CharacterData* typeToCharacter(int type);
TileData* typeToTile(ushort type);
```

Plugin for printing the player's inventory to console on `/inv` command:

```C++
#include "stdafx.h"

#include <Packets/UseItem.h>
#include <GameData/XmlData.h>

class Plugin : public IPlugin
{
public:
    Plugin(IProxy& proxy) : IPlugin(proxy)
    {
        HookCommand("inv", onCommand);
    }

    void onCommand(int argc, const char** argv)
    {
        //when printing RealmLib Strings, you need to access the c_str field (for C-style string)
        printf("%s's inventory:\n", proxy.playerData.name.c_str);
        for (size_t i = 0; i < 20; i++) //20 slots on players inventory
        {
            int item = proxy.playerData.inventory[i];
            //we need to check if the item type is valid before calling XmlData::typeToItem
            if (item == -1) //empty slot
                printf("%d: Empty\n", i);
            else if (item == 0) //inaccessible slot (backpack slot if the player doesn't have one)
                printf("%d: Unused\n", i);
            else
                printf("%d: %s\n", i, XmlData::typeToItem(item)->name);
        }
    }
};

IPlugin* create(IProxy& proxy)
{
    return new Plugin(proxy);
}

void attach(const char** plugin, const char** author, void(IPlugin::**onDisconnect)(), HookedKey** keyHook)
{
    *plugin = "ListItems";
    *author = "CrazyJani";
}
```

## What's next?

Now you're fully equipped to write your own plugins but it may be a good idea to look at other plugin sources first. The source code for all the included plugins is found on `\developer\sources`. For keyhooks you should look at the **Resend** plugin source. For disconnect callback and multi-threading, have a look at the **AbilityTimer** source. If you have made it this far, you may want to join our [Discord channel](https://discord.gg/978cV44).

Best of luck, I hope you find RealmNet useful :)
