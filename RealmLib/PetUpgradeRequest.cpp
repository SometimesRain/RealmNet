#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "PacketWriter.h"
#include "PacketReader.h"

#include <Packets/PetUpgradeRequest.h>

PetUpgradeRequest::PetUpgradeRequest(byte petTransType, int pid1, int pid2, int objectId, byte paymentTransType, const Array<SlotObject>& slots)
	: petTransType(petTransType), pid1(pid1), pid2(pid2), objectId(objectId), paymentTransType(paymentTransType), slots(slots)
{

}

PetUpgradeRequest::PetUpgradeRequest(byte* data)
{
	PacketReader r(data);

	r.read(petTransType);
	r.read(pid1);
	r.read(pid2);
	r.read(objectId);
	r.read(paymentTransType);
	r.read(slots);
}

void PetUpgradeRequest::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::PetUpgradeRequest]);

	w.write(petTransType);
	w.write(pid1);
	w.write(pid2);
	w.write(objectId);
	w.write(paymentTransType);
	w.write(slots);
}

int PetUpgradeRequest::size() const
{
	return 21 + 9 * slots.length;
}

String PetUpgradeRequest::toString() const
{
	return String("PETUPGRADEREQUEST");
}