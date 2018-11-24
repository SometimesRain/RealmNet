#pragma once

#include <Interface/IPlugin.h>

template <class ... T>
class CallbackFunc
{
private:
	IPlugin* ptr;
	void(IPlugin::*callback)(T ...);

public:
	CallbackFunc(IPlugin* ptr, void(IPlugin::*callback)(T ...));
	CallbackFunc() = delete;
	void operator()(T ... args);
};