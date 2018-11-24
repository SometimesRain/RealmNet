#include "stdafx.h"

#include "CallbackFunc.h"

template class CallbackFunc<Packet&>;
template class CallbackFunc<int, const char**>;
template class CallbackFunc<>;

template <class ... T>
CallbackFunc<T ...>::CallbackFunc(IPlugin* ptr, void(IPlugin::*callback)(T ...))
	: ptr(ptr), callback(callback)
{

}

template <class ... T>
void CallbackFunc<T ...>::operator()(T ... args)
{
	(*ptr.*callback)(args ...);
}