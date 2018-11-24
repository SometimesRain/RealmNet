#include "stdafx.h"

#include "PacketWriter.h"

PacketWriter::PacketWriter(byte* data, int size, byte id)
	: data(data), offset(0)
{
	write(size);
	write(id);
}

void PacketWriter::write(const int& val)
{
	byte* ptr = (byte*)&val;
	data[offset] = ptr[3];
	data[offset + 1] = ptr[2];
	data[offset + 2] = ptr[1];
	data[offset + 3] = ptr[0];
	offset += 4;
}

void PacketWriter::write(const float& val)
{
	byte* ptr = (byte*)&val;
	data[offset] = ptr[3];
	data[offset + 1] = ptr[2];
	data[offset + 2] = ptr[1];
	data[offset + 3] = ptr[0];
	offset += 4;
}

void PacketWriter::write(const uint& val)
{
	byte* ptr = (byte*)&val;
	data[offset] = ptr[3];
	data[offset + 1] = ptr[2];
	data[offset + 2] = ptr[1];
	data[offset + 3] = ptr[0];
	offset += 4;
}

void PacketWriter::write(const ushort& val)
{
	byte* ptr = (byte*)&val;
	data[offset] = ptr[1];
	data[offset + 1] = ptr[0];
	offset += 2;
}

void PacketWriter::write(const short& val)
{
	byte* ptr = (byte*)&val;
	data[offset] = ptr[1];
	data[offset + 1] = ptr[0];
	offset += 2;
}

void PacketWriter::write(const byte& val)
{
	data[offset] = val;
	offset++;
}

void PacketWriter::write(const bool& val)
{
	data[offset] = val;
	offset++;
}

void PacketWriter::write(const SlotObject& val)
{
	write(val.objectId);
	write(val.slotId);
	write(val.objectType);
}

void PacketWriter::write(const Location& val)
{
	write(val.x);
	write(val.y);
}

void PacketWriter::write(const MoveRecord& val)
{
	write(val.time);
	write(val.x);
	write(val.y);
}

void PacketWriter::write(const TradeItem& val)
{
	write(val.item);
	write(val.slotType);
	write(val.tradable);
	write(val.included);
}

void PacketWriter::write(const Status& val)
{
	write(val.objectId);
	write(val.position);
	write(val.data);
}

void PacketWriter::write(const StatData& val)
{
	write(val.id);

	if (val.isStringValue())
		write(val.stringValue);
	else
		write(val.intValue);
}

void PacketWriter::write(const BitmapData& val)
{
	write(val.width);
	write(val.height);

	memcpy(data + offset, val.data.data, val.data.length);
	offset += val.data.length;
}

void PacketWriter::write(const Tile& val)
{
	write(val.x);
	write(val.y);
	write(val.type);
}

void PacketWriter::write(const Entity& val)
{
	write(val.objectType);
	write(val.status);
}

void PacketWriter::write(const QuestData& val)
{
	write(val.id);
	write(val.name);
	write(val.description);
	write(val.category);
	write(val.requirements);
	write(val.rewards);
	write(val.completed);
	write(val.itemOfChoice);
	write(val.unused);
}

void PacketWriter::write(const String& val)
{
	byte* ptr = (byte*)&val.length;
	data[offset] = ptr[1];
	data[offset + 1] = ptr[0];

	memcpy(data + offset + 2, val.c_str, val.length);
	offset += 2 + val.length;
}

const char json[37] = "{\"key\":\"blank\",\"tokens\":{\"data\":\"\"}}";
void PacketWriter::writeMsg(const String& val)
{
	if (val.c_str[0] != '{')
	{
		size_t size = val.length + 36;
		byte* ptr = (byte*)&size;
		data[offset] = ptr[1];
		data[offset + 1] = ptr[0];

		memcpy(data + offset + 2, json, 33);
		memcpy(data + offset + 35, val.c_str, val.length);
		memcpy(data + offset + 35 + val.length, json + 33, 3);
		offset += 2 + size;
	}
	else
	{
		byte* ptr = (byte*)&val.length;
		data[offset] = ptr[1];
		data[offset + 1] = ptr[0];

		memcpy(data + offset + 2, val.c_str, val.length);
		offset += 2 + val.length;
	}
}

void PacketWriter::write32(const String& val)
{
	byte* ptr = (byte*)&val.length;
	data[offset] = ptr[3];
	data[offset + 1] = ptr[2];
	data[offset + 2] = ptr[1];
	data[offset + 3] = ptr[0];

	memcpy(data + offset + 4, val.c_str, val.length);
	offset += 4 + val.length;
}

void PacketWriter::write(const Array<byte>& val)
{
	byte* ptr = (byte*)&val.length;
	data[offset] = ptr[1];
	data[offset + 1] = ptr[0];

	memcpy(data + offset + 2, val.data, val.length);
	offset += 2 + val.length;
}

void PacketWriter::write8(const Array<byte>& val)
{
	data[offset] = (byte)val.length;

	memcpy(data + offset + 1, val.data, val.length);
	offset += 1 + val.length;
}

void PacketWriter::write(const Array<bool>& val)
{
	byte* ptr = (byte*)&val.length;
	data[offset] = ptr[1];
	data[offset + 1] = ptr[0];

	memcpy(data + offset + 2, val.data, val.length);
	offset += 2 + val.length;
}

void PacketWriter::write(const Array<int>& val)
{
	byte* ptr = (byte*)&val.length;
	data[offset] = ptr[1];
	data[offset + 1] = ptr[0];
	offset += 2;

	for (size_t i = 0; i < val.length; i++)
		write(val.data[i]);
}

void PacketWriter::write(const Array<MoveRecord>& val)
{
	byte* ptr = (byte*)&val.length;
	data[offset] = ptr[1];
	data[offset + 1] = ptr[0];
	offset += 2;

	for (size_t i = 0; i < val.length; i++)
		write(val.data[i]);
}

void PacketWriter::write(const Array<SlotObject>& val)
{
	byte* ptr = (byte*)&val.length;
	data[offset] = ptr[1];
	data[offset + 1] = ptr[0];
	offset += 2;

	for (size_t i = 0; i < val.length; i++)
		write(val.data[i]);
}

void PacketWriter::write(const Array<TradeItem>& val)
{
	byte* ptr = (byte*)&val.length;
	data[offset] = ptr[1];
	data[offset + 1] = ptr[0];
	offset += 2;

	for (size_t i = 0; i < val.length; i++)
		write(val.data[i]);
}

void PacketWriter::write(const Array<Status>& val)
{
	byte* ptr = (byte*)&val.length;
	data[offset] = ptr[1];
	data[offset + 1] = ptr[0];
	offset += 2;

	for (size_t i = 0; i < val.length; i++)
		write(val.data[i]);
}

void PacketWriter::write(const Array<StatData>& val)
{
	byte* ptr = (byte*)&val.length;
	data[offset] = ptr[1];
	data[offset + 1] = ptr[0];
	offset += 2;

	for (size_t i = 0; i < val.length; i++)
		write(val.data[i]);
}

void PacketWriter::write(const Array<Tile>& val)
{
	byte* ptr = (byte*)&val.length;
	data[offset] = ptr[1];
	data[offset + 1] = ptr[0];
	offset += 2;

	for (size_t i = 0; i < val.length; i++)
		write(val.data[i]);
}

void PacketWriter::write(const Array<Entity>& val)
{
	byte* ptr = (byte*)&val.length;
	data[offset] = ptr[1];
	data[offset + 1] = ptr[0];
	offset += 2;

	for (size_t i = 0; i < val.length; i++)
		write(val.data[i]);
}

void PacketWriter::write(const Array<QuestData>& val)
{
	byte* ptr = (byte*)&val.length;
	data[offset] = ptr[1];
	data[offset + 1] = ptr[0];
	offset += 2;

	for (size_t i = 0; i < val.length; i++)
		write(val.data[i]);
}

void PacketWriter::write(const Array<String>& val)
{
	byte* ptr = (byte*)&val.length;
	data[offset] = ptr[1];
	data[offset + 1] = ptr[0];
	offset += 2;

	for (size_t i = 0; i < val.length; i++)
		write(val.data[i]);
}

void PacketWriter::write32(const Array<String>& val)
{
	byte* ptr = (byte*)&val.length;
	data[offset] = ptr[1];
	data[offset + 1] = ptr[0];
	offset += 2;

	for (size_t i = 0; i < val.length; i++)
		write32(val.data[i]);
}