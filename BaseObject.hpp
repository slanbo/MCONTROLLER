#ifndef __BASEBaseObject__H
#define __BASEBaseObject__H

#include "main.h"
//#include <string>

#define MAX_OBJECT_NAME_LEN 16

class BaseObject
{
public:
	
	BaseObject();
	BaseObject(uint16_t ID, const char *Name);
	BaseObject(const char *Name);
	uint16_t _getId();
	char Name[MAX_OBJECT_NAME_LEN];

protected:	
	
	uint16_t id = 0;

	
};

#endif
