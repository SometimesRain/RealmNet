#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"
#include "PacketReader.h"

#include <Packets/File.h>

File::File(const String& filename, const String& contents)
	: filename(filename), contents(contents)
{

}

File::File(byte* data)
{
	PacketReader r(data);

	r.read(filename);
	r.read(contents);
}

void File::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::File]);

	w.write(filename);
	w.write(contents);
}

int File::size() const
{
	return 9 + filename.length + contents.length;
}

String File::toString() const
{
	return String("FILE");
}