#include "BaseObject.hpp"
#include "utf8_to_cp1251.h" 

BaseObject::BaseObject(uint16_t ID, const char *name)
	: id(ID)
{
	uint16_t lenght = convertUtf8ToCp1251(name, Name);
}

BaseObject::BaseObject(const char *name)
	: id(0xffff)
{
	uint16_t lenght = convertUtf8ToCp1251(name, Name);
}


uint16_t BaseObject::_getId()
{
	return id;
}


BaseObject::BaseObject()
{
}
