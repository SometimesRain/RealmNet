#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"
#include "PacketReader.h"

#include <Packets/AccountList.h>

AccountList::AccountList(int accountListId, const Array<String>& accountIds, int lockAction)
	: accountListId(accountListId), accountIds(accountIds), lockAction(lockAction)
{

}

AccountList::AccountList(byte* data)
{
	PacketReader r(data);

	r.read(accountListId);
	r.read(accountIds);
	r.read(lockAction);
}

void AccountList::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::AccountList]);

	w.write(accountListId);
	w.write(accountIds);
	w.write(lockAction);
}

int AccountList::size() const
{
	int size = 15 + accountIds.length;

	for (size_t i = 0; i < accountIds.length; i++)
		size += 2 + accountIds[i].length;

	return size;
}

String AccountList::toString() const
{
	return String("ACCOUNTLIST");
}