#include "stdafx.h"

#include <DataObjects/Array.h>
#include <DataObjects/StatData.h>
#include <DataObjects/MoveRecord.h>
#include <DataObjects/SlotObject.h>
#include <DataObjects/Status.h>
#include <DataObjects/TradeItem.h>
#include <DataObjects/Tile.h>
#include <DataObjects/Entity.h>
#include <DataObjects/QuestData.h>

template class Array<bool>;
template class Array<int>;
template class Array<byte>;
template class Array<StatData>;
template class Array<MoveRecord>;
template class Array<SlotObject>;
template class Array<String>;
template class Array<Status>;
template class Array<TradeItem>;
template class Array<Tile>;
template class Array<Entity>;
template class Array<QuestData>;

template <class T>
Array<T>::Array()
	: length(0), data(nullptr) //deleting nullptr does nothing (C++14)
{

}

template <class T>
Array<T>::Array(T* data, size_t size)
	: length(size), data(data)
{

}

template <class T>
Array<T>::Array(const Array<T>& array)
	: length(array.length), data(new T[length])
{
	//length = array.length;
	//data = new T[length];
	memcpy(data, array.data, length * sizeof T);
}

/*template <class T>
Array<T>::Array(Array<T>&& array) noexcept
{
	length = array.length;
	data = array.data;
}*/

template <class T>
Array<T>::~Array()
{
	delete[] data;
}

template <class T>
T& Array<T>::operator[](size_t index) const
{
	return data[index];
}

template <class T>
void Array<T>::operator=(const Array<T>& array)
{
	length = array.length;
	T* newData = new T[length];
	memcpy(newData, array.data, length * sizeof T);

	delete[] data;
	data = newData;
}

template <class T>
void Array<T>::reserve(size_t size) //TODO implement capacity variable?
{
	T* newData = new T[size];
	memcpy(newData, data, length * sizeof T);

	delete[] data;
	data = newData;
}

template <class T>
void Array<T>::emplace_back(T& item)
{
	data[length++] = item;
}