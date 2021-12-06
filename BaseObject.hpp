#ifndef __BASEBaseObject__H
#define __BASEBaseObject__H

//#include "main.h"
#include <string>

class BaseObject
{
public:
	
	BaseObject();
	BaseObject(uint16_t ID, std::string name);
	BaseObject(std::string name);
	uint16_t _getId();
	char Name[16];

protected:	
	
	uint16_t id = 0;

	
};

#endif
