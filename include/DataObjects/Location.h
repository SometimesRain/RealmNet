#pragma once

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API Location
{
public:
	float x;
	float y;

	Location(float x, float y);
	Location();
};