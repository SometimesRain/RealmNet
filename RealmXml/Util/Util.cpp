#include "stdafx.h"

#include "Util.h"

int Util::occurences(const char* text, const char* pattern)
{
	int count = 0;
	const char* temp = text;
	while (temp = strstr(temp, pattern))
		count++, temp++;
	return count;
}