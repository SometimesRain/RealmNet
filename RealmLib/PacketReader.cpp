#include "stdafx.h"

#include "PacketReader.h"

PacketReader::PacketReader(byte* data)
	: data(data), offset(5)
{

}

bool PacketReader::more()
{
	int length = 0;
	byte* ptr = (byte*)&length;
	ptr[3] = data[0];
	ptr[2] = data[1];
	ptr[1] = data[2];
	ptr[0] = data[3];

	return length > offset;
}

void PacketReader::read(int& val)
{
	byte* ptr = (byte*)&val;
	ptr[3] = data[offset];
	ptr[2] = data[offset + 1];
	ptr[1] = data[offset + 2];
	ptr[0] = data[offset + 3];
	offset += 4;
}

void PacketReader::read(float& val)
{
	byte* ptr = (byte*)&val;
	ptr[3] = data[offset];
	ptr[2] = data[offset + 1];
	ptr[1] = data[offset + 2];
	ptr[0] = data[offset + 3];
	offset += 4;
}

void PacketReader::read(uint& val)
{
	byte* ptr = (byte*)&val;
	ptr[3] = data[offset];
	ptr[2] = data[offset + 1];
	ptr[1] = data[offset + 2];
	ptr[0] = data[offset + 3];
	offset += 4;
}

void PacketReader::read(ushort& val)
{
	byte* ptr = (byte*)&val;
	ptr[1] = data[offset];
	ptr[0] = data[offset + 1];
	offset += 2;
}

void PacketReader::read(short& val)
{
	byte* ptr = (byte*)&val;
	ptr[1] = data[offset];
	ptr[0] = data[offset + 1];
	offset += 2;
}

void PacketReader::read(byte& val)
{
	val = data[offset];
	offset++;
}

void PacketReader::read(bool& val)
{
	val = data[offset];
	offset++;
}

void PacketReader::read(SlotObject& val)
{
	read(val.objectId);
	read(val.slotId);
	read(val.objectType);
}

void PacketReader::read(Location& val)
{
	read(val.x);
	read(val.y);
}

void PacketReader::read(MoveRecord& val)
{
	read(val.time);
	read(val.x);
	read(val.y);
}

void PacketReader::read(TradeItem& val)
{
	read(val.item);
	read(val.slotType);
	read(val.tradable);
	read(val.included);
}

void PacketReader::read(Status& val)
{
	read(val.objectId);
	read(val.position);
	read(val.data);
}

void PacketReader::read(StatData& val)
{
	read(val.id);

	if (val.isStringValue())
		read(val.stringValue);
	else
		read(val.intValue);
}

void PacketReader::read(BitmapData& val)
{
	read(val.width);
	read(val.height);

	int size = val.width * val.height * 4;
	memcpy(val.data.data, data + offset, size);
	offset += size;
}

void PacketReader::read(Tile& val)
{
	read(val.x);
	read(val.y);
	read(val.type);
}

void PacketReader::read(Entity& val)
{
	read(val.objectType);
	read(val.status);
}

void PacketReader::read(QuestData& val)
{
	read(val.id);
	read(val.name);
	read(val.description);
	read(val.category);
	read(val.requirements);
	read(val.rewards);
	read(val.completed);
	read(val.itemOfChoice);
	read(val.unused);
}

void PacketReader::read(String& val)
{
	byte* ptr = (byte*)&val.length;
	ptr[1] = data[offset];
	ptr[0] = data[offset + 1];

	char* newData = new char[val.length + 1];
	memcpy(newData, data + offset + 2, val.length);
	newData[val.length] = 0; //null terminator

	delete[] val.c_str;
	val.c_str = newData;

	offset += 2 + val.length;
}

void PacketReader::read32(String& val)
{
	byte* ptr = (byte*)&val.length;
	ptr[3] = data[offset];
	ptr[2] = data[offset + 1];
	ptr[1] = data[offset + 2];
	ptr[0] = data[offset + 3];

	char* newData = new char[val.length + 1];
	memcpy(newData, data + offset + 4, val.length);
	newData[val.length] = 0; //null terminator

	delete[] val.c_str;
	val.c_str = newData;

	offset += 4 + val.length;
}

void PacketReader::read(Array<byte>& val)
{
	byte* ptr = (byte*)&val.length;
	ptr[1] = data[offset];
	ptr[0] = data[offset + 1];

	byte* newData = new byte[val.length];
	memcpy(newData, data + offset + 2, val.length);

	delete[] val.data;
	val.data = newData;

	offset += 2 + val.length;
}

void PacketReader::read8(Array<byte>& val)
{
	val.length = data[offset];

	byte* newData = new byte[val.length];
	memcpy(newData, data + offset + 1, val.length);

	delete[] val.data;
	val.data = newData;

	offset += 1 + val.length;
}

void PacketReader::read(Array<bool>& val)
{
	byte* ptr = (byte*)&val.length;
	ptr[1] = data[offset];
	ptr[0] = data[offset + 1];

	bool* newData = new bool[val.length];
	memcpy(newData, data + offset + 2, val.length);

	delete[] val.data;
	val.data = newData;

	offset += 2 + val.length;
}

void PacketReader::read(Array<int>& val)
{
	byte* ptr = (byte*)&val.length;
	ptr[1] = data[offset];
	ptr[0] = data[offset + 1];
	offset += 2;

	int* newData = new int[val.length];
	for (size_t i = 0; i < val.length; i++)
		read(newData[i]);

	delete[] val.data;
	val.data = newData;
}

void PacketReader::read(Array<MoveRecord>& val)
{
	byte* ptr = (byte*)&val.length;
	ptr[1] = data[offset];
	ptr[0] = data[offset + 1];
	offset += 2;

	MoveRecord* newData = new MoveRecord[val.length];
	for (size_t i = 0; i < val.length; i++)
		read(newData[i]);

	delete[] val.data;
	val.data = newData;
}

void PacketReader::read(Array<SlotObject>& val)
{
	byte* ptr = (byte*)&val.length;
	ptr[1] = data[offset];
	ptr[0] = data[offset + 1];
	offset += 2;

	SlotObject* newData = new SlotObject[val.length];
	for (size_t i = 0; i < val.length; i++)
		read(newData[i]);

	delete[] val.data;
	val.data = newData;
}

void PacketReader::read(Array<TradeItem>& val)
{
	byte* ptr = (byte*)&val.length;
	ptr[1] = data[offset];
	ptr[0] = data[offset + 1];
	//printf("offset %d new size %d %02x %02x\n", offset, val.length, data[offset], data[offset + 1]);
	offset += 2;

	TradeItem* newData = new TradeItem[val.length];
	for (size_t i = 0; i < val.length; i++)
		read(newData[i]);

	delete[] val.data;
	val.data = newData;
}

void PacketReader::read(Array<Status>& val)
{
	byte* ptr = (byte*)&val.length;
	ptr[1] = data[offset];
	ptr[0] = data[offset + 1];
	offset += 2;

	Status* newData = new Status[val.length];
	for (size_t i = 0; i < val.length; i++)
		read(newData[i]);

	delete[] val.data;
	val.data = newData;
}

void PacketReader::read(Array<StatData>& val)
{
	byte* ptr = (byte*)&val.length;
	ptr[1] = data[offset];
	ptr[0] = data[offset + 1];
	offset += 2;

	StatData* newData = new StatData[val.length];
	for (size_t i = 0; i < val.length; i++)
		read(newData[i]);

	delete[] val.data;
	val.data = newData;
}

void PacketReader::read(Array<Tile>& val)
{
	byte* ptr = (byte*)&val.length;
	ptr[1] = data[offset];
	ptr[0] = data[offset + 1];
	offset += 2;

	Tile* newData = new Tile[val.length];
	for (size_t i = 0; i < val.length; i++)
		read(newData[i]);

	delete[] val.data;
	val.data = newData;
}

void PacketReader::read(Array<Entity>& val)
{
	byte* ptr = (byte*)&val.length;
	ptr[1] = data[offset];
	ptr[0] = data[offset + 1];
	offset += 2;

	Entity* newData = new Entity[val.length];
	for (size_t i = 0; i < val.length; i++)
		read(newData[i]);

	delete[] val.data;
	val.data = newData;
}

void PacketReader::read(Array<QuestData>& val)
{
	byte* ptr = (byte*)&val.length;
	ptr[1] = data[offset];
	ptr[0] = data[offset + 1];
	offset += 2;

	QuestData* newData = new QuestData[val.length];
	for (size_t i = 0; i < val.length; i++)
		read(newData[i]);

	delete[] val.data;
	val.data = newData;
}

void PacketReader::read(Array<String>& val)
{
	byte* ptr = (byte*)&val.length;
	ptr[1] = data[offset];
	ptr[0] = data[offset + 1];
	offset += 2;

	String* newData = new String[val.length];
	for (size_t i = 0; i < val.length; i++)
		read(newData[i]);

	delete[] val.data;
	val.data = newData;
}

void PacketReader::read32(Array<String>& val)
{
	byte* ptr = (byte*)&val.length;
	ptr[1] = data[offset];
	ptr[0] = data[offset + 1];
	offset += 2;

	String* newData = new String[val.length];
	for (size_t i = 0; i < val.length; i++)
		read32(newData[i]);

	delete[] val.data;
	val.data = newData;
}