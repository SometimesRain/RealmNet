#include "stdafx.h"

#include "Random.h"

uint x = 123456789, y = 362436069, z = 521288629;

uint Random::xorshf96() //period 2^96-1
{
	uint t;
	x ^= x << 16;
	x ^= x >> 5;
	x ^= x << 1;

	t = x;
	x = y;
	y = z;
	z = t ^ x ^ y;

	return z;
}