#include "stdafx.h"

#include <Interface/IPlugin.h>

HookedKey::HookedKey(byte vkKey, byte modifier, bool global, void(IPlugin::*callback)(bool))
	: vkKey(vkKey), modifier(modifier), global(global), callback(callback)
{

}