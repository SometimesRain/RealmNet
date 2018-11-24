#include "stdafx.h"

#include <string.h>

#include <DataObjects/String.h>

String::String()
{
	length = 0;
	c_str = new char[length + 1];
	c_str[length] = 0; //null terminator
}

String::String(const char* string)
{
	length = strlen(string);
	c_str = new char[length + 1];
	memcpy(c_str, string, length);
	c_str[length] = 0; //null terminator
}

String::String(char* buffer, size_t size)
{
	length = size;
	c_str = buffer;
}

String::String(const String& string)
{
	length = string.length;
	c_str = new char[length + 1];
	memcpy(c_str, string.c_str, length);
	c_str[length] = 0; //null terminator
}

String::~String()
{
	//printf("freed %d at %x\n", length, data);
	delete[] c_str;
}

void String::operator=(const char* string)
{
	length = strlen(string);
	char* newData = new char[length + 1];
	memcpy(newData, string, length);
	newData[length] = 0; //null terminator

	delete[] c_str;
	c_str = newData;
}

void String::operator=(const String& string)
{
	length = string.length;
	char* newData = new char[length + 1];
	memcpy(newData, string.c_str, length);
	newData[length] = 0; //null terminator

	delete[] c_str;
	c_str = newData;
}

bool String::operator==(const char* string)
{
	if (length != strlen(string))
		return false;

	for (size_t i = 0; i < length; i++)
		if (c_str[i] != string[i])
			return false;

	return true;
}

bool String::operator!=(const char* string)
{
	return !operator==(string);
}