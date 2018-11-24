#include "stdafx.h"

#include "KeyHook.h"
#include <GameData/Constants.h>

//TODO
//allow hooking keys from proxy (hookKeyDown, hookKeyUp, hookGlobalKeyDown, hookGlobalKeyUp)
//hold references to all active proxy instances (for global hotkeys)
//Acceptor add most Proxy* recentActivity (and set it on Move if position changed, old pos in playerdata)

Proxy* KeyHook::recentActivity;
std::vector<std::vector<HookedKey*>> KeyHook::hookedKeys;

std::vector<Proxy*> proxies;

HHOOK hKeyboardHook;
int modifiers = Modifier::None;
bool keys[0xff];

LRESULT CALLBACK KeyboardEvent(int nCode, WPARAM wParam, LPARAM lParam);
DWORD WINAPI MonitorHotkeys(LPVOID lpParm);

void KeyHook::add(Proxy* proxy)
{
	proxies.push_back(proxy);
}

void KeyHook::remove(Proxy* proxy)
{
	if (KeyHook::recentActivity == proxy)
		KeyHook::recentActivity = nullptr;
	for (size_t i = 0; i < proxies.size(); i++)
	{
		if (proxies[i] == proxy)
		{
			proxies.erase(proxies.begin() + i);
			return;
		}
	}
}

void KeyHook::monitorKeys()
{
	HANDLE hThread;
	DWORD dwThread;

	memset(keys, 0, 0xff);
	hThread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MonitorHotkeys, NULL, NULL, &dwThread);
}

//----------------- WINAPI FUNCTIONS ------------------

void fireCallbacks(DWORD vkCode, bool down)
{
	for (size_t i = 0; i < KeyHook::hookedKeys.size(); i++)
		for (auto& key : KeyHook::hookedKeys[i])
			if (vkCode == key->vkKey && (key->modifier == Modifier::Any || key->modifier == modifiers)) //the any flag or all the same flags
				if (key->global)
					for (Proxy*& proxy : proxies)
						(*proxy->plugins[i].*key->callback)(down);
				else if (KeyHook::recentActivity)
					(*KeyHook::recentActivity->plugins[i].*key->callback)(down);

	keys[vkCode] = down;
}

bool isFlashWindow()
{
	char windowTitle[256];
	HWND hwnd = GetForegroundWindow();
	GetWindowTextA(hwnd, windowTitle, sizeof(windowTitle));
	if (windowTitle[0] == 'A')
	{
		windowTitle[18] = 0; //add null terminator
		if (strcmp(windowTitle, "Adobe Flash Player") == 0)
			return true;
	}
	else if (strcmp(windowTitle, "Realm of the Mad God") == 0)
	{
		return true;
	}
	return false;
}

LRESULT CALLBACK KeyboardEvent(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HC_ACTION && isFlashWindow())
	{
		KBDLLHOOKSTRUCT& hookedKey = *(KBDLLHOOKSTRUCT*)lParam;
		if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)
		{
			if (hookedKey.vkCode == VK_LSHIFT || hookedKey.vkCode == VK_RSHIFT)
				modifiers |= Modifier::Shift;
			else if (hookedKey.vkCode == VK_LCONTROL || hookedKey.vkCode == VK_RCONTROL)
				modifiers |= Modifier::Control;
			else if (hookedKey.vkCode == VK_LMENU)
				modifiers |= Modifier::Alt;

			if (!keys[hookedKey.vkCode])
				fireCallbacks(hookedKey.vkCode, true);
		}
		else if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP)
		{
			if (hookedKey.vkCode == VK_LSHIFT || hookedKey.vkCode == VK_RSHIFT)
				modifiers &= ~Modifier::Shift;
			else if (hookedKey.vkCode == VK_LCONTROL || hookedKey.vkCode == VK_RCONTROL)
				modifiers &= ~Modifier::Control;
			else if (hookedKey.vkCode == VK_LMENU)
				modifiers &= ~Modifier::Alt;

			fireCallbacks(hookedKey.vkCode, false);
		}
	}

	return CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
}

DWORD WINAPI MonitorHotkeys(LPVOID lpParm)
{
	HINSTANCE hInstance = GetModuleHandleA(NULL);
	if (!hInstance) return 1;

	hKeyboardHook = SetWindowsHookExA(WH_KEYBOARD_LL, (HOOKPROC)KeyboardEvent, hInstance, NULL);

	MSG message;
	while (GetMessage(&message, NULL, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	UnhookWindowsHookEx(hKeyboardHook);
	return 0;
}

/*void KeyHook::hookKeyDown(byte vkKey, byte modifier, void(*callback)())
{
downCallbacks.push_back(std::make_pair(ModifiedKey(vkKey, modifier), callback));
}

void KeyHook::hookKeyUp(byte vkKey, byte modifier, void(*callback)())
{
upCallbacks.push_back(std::make_pair(ModifiedKey(vkKey, modifier), callback));
}

bool KeyHook::keyDown(byte vkKey, byte modifier)
{
return keys[vkKey] && (modifier == Modifier::Any || modifier == modifiers);
}*/