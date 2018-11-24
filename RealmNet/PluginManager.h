#pragma once

#include <Interface/IPlugin.h>

namespace PluginManager
{
	extern std::vector<IPlugin*(*)(IProxy&)> instantiators;
	extern std::vector<void(IPlugin::*)()> disconnectCallbacks;

	void attachPlugins();
}