#include "TuneObjectsExt.hpp"
#include "eeprom.h"
#include "rtc.h"
#include "SocketObjectsExt.hpp"
#include "Auxiliary.h"

void readTunesFromFlash()
{
	FlashTune* cursor  = lastFlashTune;
	while (cursor->getPrevFlashTune() != nullptr)
	{
		cursor->restore();
		cursor = cursor->getPrevFlashTune();
	}
}

void writesTunesToFlash()
{
	FlashTune* cursor  = lastFlashTune;
	while (cursor->getPrevFlashTune() != nullptr)
	{
		cursor->save();
		cursor = cursor->getPrevFlashTune();
	}
}

void clearTunesInFlash()
{
	FlashTune* cursor  = lastFlashTune;
	while (cursor->getPrevFlashTune() != nullptr)
	{
		cursor->clear();
		cursor = cursor->getPrevFlashTune();
	}
}

void setDefaultTuneVals()
{
	std::vector<uint16_t> defs = { 0, 0 };
	
	if (airTempControlSensors.undefined())
	{
		defs[0] = 2;
		defs[1] = 3;
		airTempControlSensors._setVal(defs);	
		airTempControlSensors.save();
	}
		
	if (airTempControlUpSockets.undefined())
	{
		defs[0] = 1;
		defs[1] = 0;
		airTempControlUpSockets._setVal(defs);
	}
	
	//bat Temp control sensors & sockets
	if (batTempControlSensors.undefined())
	{
		defs[0] = 3;
		defs[1] = 0;
		batTempControlSensors._setVal(defs);
	}
	if (batTempControlUpSockets.undefined())
	{
		defs[0] = 2;
		defs[1] = 0;
		batTempControlUpSockets._setVal(defs);	
	}

	//light control sensors & sockets
	if (lightControlSensors.undefined())
	{
		defs[0] = 4;
		defs[1] = 0;
		lightControlSensors._setVal(defs);	
	}
	if (lightControlUpSockets.undefined())
	{
		defs[0] = 2;
		defs[1] = 0;
		lightControlUpSockets._setVal(defs);	
	}

	//co control sensors sockets
	if (COControlSensors.undefined())
	{
		defs[0] = 1;
		defs[1] = 0;
		COControlSensors._setVal(defs);	
	}
	if (COControlUpSockets.undefined())
	{
		defs[0] = 3;
		defs[1] = 0;
		COControlUpSockets._setVal(defs);	
	}

	//humodity control sensors sockets
	if (humidityControlSensors.undefined())
	{
		
	}
	if (humidityControlUpSockets.undefined())
	{
		
	}
}

