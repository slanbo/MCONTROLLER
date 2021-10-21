#include "BaseObject.hpp"
#include "utf8_to_cp1251.h" 

BaseObject::BaseObject(uint16_t ID, std::string name)
	: id(ID)
{
	const char* charstr = name.c_str();
	convertUtf8ToCp1251(charstr, Name);
}

BaseObject::BaseObject(std::string name)
	: id(0xffff)
{
	const char* charstr = name.c_str();
	convertUtf8ToCp1251(charstr, Name);
}


uint16_t BaseObject::_getId()
{
	return id;
}
