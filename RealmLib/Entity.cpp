#include "stdafx.h"

#include <DataObjects/Entity.h>

Entity::Entity(ushort objectType, const Status& status)
	: objectType(objectType), status(status)
{

}

Entity::Entity()
{

}