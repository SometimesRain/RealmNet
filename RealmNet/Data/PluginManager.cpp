#include "stdafx.h"

#include "PluginManager.h"
#include "KeyHook.h"

std::vector<IPlugin*(*)(IProxy&)> PluginManager::instantiators;
std::vector<void(IPlugin::*)()> PluginManager::disconnectCallbacks;

void attachPlugin(const char* filename)
{
	HINSTANCE dllHandle = LoadLibraryA(filename);

	if (!dllHandle)
		return;

	typedef void(*f_attach)(const char**, const char**, void(IPlugin::**)(), HookedKey**);
	f_attach attach = (f_attach)GetProcAddress(dllHandle, "attach");
	IPlugin*(*create)(IProxy&) = (IPlugin*(*)(IProxy&))GetProcAddress(dllHandle, "create");
	if (!attach || !create)
	{
		FreeLibrary(dllHandle);
		return;
	}

	const char* plugin = nullptr;
	const char* author = nullptr;
	void(IPlugin::*disconnectCallback)() = nullptr;
	HookedKey* keyHook[0xff]{};
	HookedKey** endPtr = keyHook;

	attach(&plugin, &author, &disconnectCallback, keyHook);
	KeyHook::hookedKeys.push_back(std::vector<HookedKey*>());
#ifndef _DEBUG
	while (*endPtr)
	{
		KeyHook::hookedKeys.back().push_back((*endPtr++));
	}
#endif

	PluginManager::instantiators.push_back(create);
	PluginManager::disconnectCallbacks.push_back(disconnectCallback);
	printf("Attached %s by %s", plugin, author);
	if (KeyHook::hookedKeys.back().size() > 0)
		printf(" (%d %s hooked)", KeyHook::hookedKeys.back().size(), KeyHook::hookedKeys.back().size() == 1 ? "key" : "keys");
	printf("\n");
}

void PluginManager::attachPlugins()
{
	boost::filesystem::path p(".");
	if (boost::filesystem::is_directory(p))
	{
		for (auto& entry : boost::make_iterator_range(boost::filesystem::directory_iterator(p), {}))
		{
			std::string file = entry.path().string();
			if (file.substr(file.size() - 4, 4) == ".dll")
				attachPlugin(file.c_str());
		}
	}
}