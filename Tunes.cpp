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
		defs[1] = 0;
		airTempControlSensors._setVal(defs);	
	}
		
	if (airTempControlSockets.undefined())
	{
		defs[0] = 1;
		defs[1] = 0;
		airTempControlSockets._setVal(defs);
	}

	//bat Temp control sensors & sockets
	if (batTempControlSensors.undefined())
	{
		defs[0] = 3;
		defs[1] = 0;
		batTempControlSensors._setVal(defs);
	}
	if (batTempControlSockets.undefined())
	{
		defs[0] = 2;
		defs[1] = 0;
		batTempControlSockets._setVal(defs);	
	}

	//light control sensors & sockets
	if (lightControlSensors.undefined())
	{
		defs[0] = 4;
		defs[1] = 0;
		lightControlSensors._setVal(defs);	
	}
	if (lightControlSockets.undefined())
	{
		defs[0] = 2;
		defs[1] = 0;
		lightControlSensors._setVal(defs);	
	}

	//co control sensors sockets
	if (COControlSensors.undefined())
	{
		defs[0] = 1;
		defs[1] = 0;
		COControlSensors._setVal(defs);	
	}
	if (COControlSockets.undefined())
	{
		defs[0] = 3;
		defs[1] = 0;
		COControlSockets._setVal(defs);	
	}

	//humodity control sensors sockets
	if (humidityControlSensors.undefined())
	{
		
	}
	if (humidityControlSockets.undefined())
	{
		
	}
}

