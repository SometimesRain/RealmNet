#pragma once

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

template <class T>
class PACKET_API Array
{
public:
	size_t length;
	T* data;

	Array();
	Array(T* data, size_t size);
	Array(const Array<T>& array);
	//Array(Array<T>&& array) noexcept;
	~Array();

	T& operator[](size_t index) const;
	void operator=(const Array<T>& array);

	void reserve(size_t size);
	void emplace_back(T& item);
};