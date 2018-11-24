#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "Packets/PacketWriter.h"
#include "Packets/PacketReader.h"

#include <Packets/PasswordPrompt.h>

PasswordPrompt::PasswordPrompt(int cleanPasswordStatus)
	: cleanPasswordStatus(cleanPasswordStatus)
{

}

PasswordPrompt::PasswordPrompt(byte* data)
{
	PacketReader r(data);

	r.read(cleanPasswordStatus);
}

void PasswordPrompt::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::PasswordPrompt]);

	w.write(cleanPasswordStatus);
}

int PasswordPrompt::size() const
{
	return 9;
}

String PasswordPrompt::toString() const
{
	return String("PASSWORDPROMPT");
}