#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "Packets/PacketWriter.h"
#include "Packets/PacketReader.h"

#include <Packets/EditAccountList.h>

EditAccountList::EditAccountList(int accountListId, bool add, int objectId)
	: accountListId(accountListId), add(add), objectId(objectId)
{

}

EditAccountList::EditAccountList(byte* data)
{
	PacketReader r(data);

	r.read(accountListId);
	r.read(add);
	r.read(objectId);
}

void EditAccountList::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::EditAccountList]);

	w.write(accountListId);
	w.write(add);
	w.write(objectId);
}

int EditAccountList::size() const
{
	return 14;
}

String EditAccountList::toString() const
{
	return String("EDITACCOUNTLIST");
}