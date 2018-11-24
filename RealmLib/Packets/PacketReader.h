#pragma once

#include <DataObjects/SlotObject.h>
#include <DataObjects/Location.h>
#include <DataObjects/MoveRecord.h>
#include <DataObjects/TradeItem.h>
#include <DataObjects/Status.h>
#include <DataObjects/BitmapData.h>
#include <DataObjects/Tile.h>
#include <DataObjects/Entity.h>
#include <DataObjects/QuestData.h>

class PacketReader
{
private:
	int offset;
	byte* data;

public:
	PacketReader(byte* data);

	bool more();

	void read(int& val);
	void read(float& val);
	void read(uint& val);
	void read(ushort& val);
	void read(short& val);

	void read(byte& val);
	void read(bool& val);

	void read(SlotObject& val);
	void read(Location& val);
	void read(MoveRecord& val);
	void read(TradeItem& val);
	void read(Status& val);
	void read(StatData& val);
	void read(BitmapData& val);
	void read(Tile& val);
	void read(Entity& val);
	void read(QuestData& val);

	void read(String& val);
	void read32(String& val);
	void read(Array<byte>& val);
	void read8(Array<byte>& val);
	void read(Array<bool>& val);
	void read(Array<int>& val);
	void read(Array<MoveRecord>& val);
	void read(Array<SlotObject>& val);
	void read(Array<TradeItem>& val);
	void read(Array<Status>& val);
	void read(Array<StatData>& val);
	void read(Array<Tile>& val);
	void read(Array<Entity>& val);
	void read(Array<QuestData>& val);
	void read(Array<String>& val);
	void read32(Array<String>& val);
};