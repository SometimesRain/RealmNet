#include "stdafx.h"

#include "RC4Cipher.h"

RC4Cipher::RC4Cipher(const byte* key)
{
	workingKey = (byte*)key;
	reset();
}

void RC4Cipher::reset()
{
	x = y = 0;

	for (size_t i = 0; i < 256; i++)
		engineState[i] = (byte)i;

	int a = 0;
	int b = 0;

	for (size_t i = 0; i < 256; i++)
	{
		b = ((workingKey[a] & 0xff) + engineState[i] + b) & 0xff;

		//swap
		std::swap(engineState[i], engineState[b]);

		a = (a + 1) % 13; //% keylength
	}
}

void RC4Cipher::cipher(byte* buffer, int size)
{
	for (size_t i = 0; i < size; i++)
	{
		x = (x + 1) & 0xff;
		y = (engineState[x] + y) & 0xff;

		//swap
		std::swap(engineState[x], engineState[y]);

		//xor
		buffer[i] ^= engineState[(engineState[x] + engineState[y]) & 0xff];
	}
}