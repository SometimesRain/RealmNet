#pragma once

#include <DataObjects/String.h>
#include <DataObjects/Array.h>

#ifdef LIB
#define PACKET_API __declspec(dllexport)
#else
#define PACKET_API __declspec(dllimport)
#endif

class PACKET_API QuestData
{
public:
	String id;
	String name;
	String description;
	int category;
	Array<int> requirements;
	Array<int> rewards;
	bool completed;
	bool itemOfChoice;
	byte unused = 0;

	QuestData(const String& id, const String& name, const String& description, int category, const Array<int>& requirements, const Array<int>& rewards, bool completed, bool itemOfChoice);
	QuestData();
};