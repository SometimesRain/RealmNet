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

class PacketWriter
{
private:
	int offset;
	byte* data;

public:
	PacketWriter(byte* data, int size, byte id);

	void write(const int& val);
	void write(const float& val);
	void write(const uint& val);
	void write(const ushort& val);
	void write(const short& val);

	void write(const byte& val);
	void write(const bool& val);

	void write(const SlotObject& val);
	void write(const Location& val);
	void write(const MoveRecord& val);
	void write(const TradeItem& val);
	void write(const Status& val);
	void write(const StatData& val);
	void write(const BitmapData& val);
	void write(const Tile& val);
	void write(const Entity& val);
	void write(const QuestData& val);

	void write(const String& val);
	void writeMsg(const String& val);
	void write32(const String& val);
	void write(const Array<byte>& val);
	void write8(const Array<byte>& val);
	void write(const Array<bool>& val);
	void write(const Array<int>& val);
	void write(const Array<MoveRecord>& val);
	void write(const Array<SlotObject>& val);
	void write(const Array<TradeItem>& val);
	void write(const Array<Status>& val);
	void write(const Array<StatData>& val);
	void write(const Array<Tile>& val);
	void write(const Array<Entity>& val);
	void write(const Array<QuestData>& val);
	void write(const Array<String>& val);
	void write32(const Array<String>& val);
};