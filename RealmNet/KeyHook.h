#pragma once

#include "Proxy.h"

namespace KeyHook
{
	extern Proxy* recentActivity;
	extern std::vector<std::vector<HookedKey*>> hookedKeys;

	void add(Proxy* proxy);
	void remove(Proxy* proxy);

	void monitorKeys();
}