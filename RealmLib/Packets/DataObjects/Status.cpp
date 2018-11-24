#include "stdafx.h"

#include <DataObjects/Status.h>

Status::Status(int objectId, const Location& position, const Array<StatData>& data)
	: objectId(objectId), position(position), data(data)
{

}

Status::Status()
{

}