#include "stdafx.h"

#include <DataObjects/QuestData.h>

QuestData::QuestData(const String& id, const String& name, const String& description, int category, const Array<int>& requirements, const Array<int>& rewards, bool completed, bool itemOfChoice)
	: id(id), name(name), description(description), category(category), requirements(requirements), rewards(rewards), completed(completed), itemOfChoice(itemOfChoice)
{

}

QuestData::QuestData()
{

}