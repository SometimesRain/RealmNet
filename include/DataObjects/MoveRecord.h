#pragma once

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API MoveRecord
{
public:
	int time;
	float x;
	float y;

	MoveRecord(int time, float x, float y);
	MoveRecord();
};