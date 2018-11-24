#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "Packets/PacketWriter.h"

#include <Packets/VerifyEmail.h>

VerifyEmail::VerifyEmail()
{

}

VerifyEmail::VerifyEmail(byte* data)
{

}

void VerifyEmail::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::VerifyEmail]);
}

int VerifyEmail::size() const
{
	return 5;
}

String VerifyEmail::toString() const
{
	return String("VERIFYEMAIL");
}