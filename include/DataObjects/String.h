#pragma once

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API String
{
public:
	size_t length;
	char* c_str;

	String();
	String(const char* string);
	String(char* buffer, size_t size);
	String(const String& string);
	~String();

	void operator=(const char* string);
	void operator=(const String& string);

	bool operator==(const char* string);
	bool operator!=(const char* string);
};