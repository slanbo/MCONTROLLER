#include "BaseObject.hpp"
#include "utf8_to_cp1251.h" 

BaseObject::BaseObject(uint16_t ID, const char *name)
	: id(ID)
{
	for(int i = 0 ; i < MAX_OBJECT_NAME_LEN - 1 ; i++) {
		Name[i] = *name;
		if (*name == 0)
			break;
		name++;
	}
	Name[MAX_OBJECT_NAME_LEN - 1] = 0;
	
	
}

BaseObject::BaseObject(const char *name)
	: id(0xffff)
{
	for (int i = 0; i < MAX_OBJECT_NAME_LEN - 1; i++) {
		Name[i] = *name;
		if (*name == 0)
			break;
		name++;
	}
	Name[MAX_OBJECT_NAME_LEN - 1] = 0;
}


uint16_t BaseObject::_getId()
{
	return id;
}


BaseObject::BaseObject()
{
}
