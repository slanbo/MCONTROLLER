#include "TuneObjectsExt.hpp"
#include "eeprom.h"
#include "rtc.h"
#include "SocketObjectsExt.hpp"
#include "Auxiliary.h"

void readTunesFromFlash()
{
	FlashTune* cursor  = lastFlashTune;
	do {
		cursor->restore();
		cursor = cursor->getPrevFlashTune();
	} while (cursor->getPrevFlashTune() != nullptr);
	cursor->restore();
	
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
	
	upSocketLoadPower._setVal(1000);
	upSocketLoadPower.save();
	
	downSocketLoadPower._setVal(2000);
	downSocketLoadPower.save();
	
	v12LoadPower._setVal(100);
	v12LoadPower.save();
	
	//if (airTempControlSensors.undefined())
	//{
		defs[0] = 2;
		defs[1] = 0xffff;
		airTempControlSensors._setVal(defs);	
		airTempControlSensors.save();
	//}
		
	//if (airTempControlUpSockets.undefined())
	//{
		defs[0] = 1;
		defs[1] = 0xffff;
		airTempControlUpSockets._setVal(defs);
		airTempControlUpSockets.save();
	//}
	
	//if (airTempControlDownSockets.undefined())
	//{
		defs[0] = 0xffff;
		defs[1] = 0xffff;
		airTempControlDownSockets._setVal(defs);
		airTempControlDownSockets.save();
	//}
	
	//bat Temp control sensors & sockets
	//if (batTempControlSensors.undefined())
	//{
		defs[0] = 3;
		defs[1] = 0xffff;
		batTempControlSensors._setVal(defs);
		batTempControlSensors.save();
	//}
	
	//if (batTempControlUpSockets.undefined())
	//{
		defs[0] = 0;
		defs[1] = 0xffff;
		batTempControlUpSockets._setVal(defs);
		batTempControlUpSockets.save();
	//}

	//if (batTempControlDownSockets.undefined())
	//{
		defs[0] = 0xffff;
		defs[1] = 0xffff;
		batTempControlDownSockets._setVal(defs);
		batTempControlDownSockets.save();
	//}	
	//light control sensors & sockets
	//if (lightControlSensors.undefined())
	//{
		defs[0] = 4;
		defs[1] = 0xffff;
		lightControlSensors._setVal(defs);	
		lightControlSensors.save();
	//}
	//if (lightControlUpSockets.undefined())
	//{
		defs[0] = 0xffff;
		defs[1] = 0xffff;
		lightControlUpSockets._setVal(defs);	
		lightControlUpSockets.save();
	//}

		defs[0] = 0xffff;
		defs[1] = 0xffff;
		lightControlDownSockets._setVal(defs);	
		lightControlDownSockets.save();
	
	//co control sensors sockets
	//if (COControlSensors.undefined())
	//{
		defs[0] = 1;
		defs[1] = 0xffff;
		COControlSensors._setVal(defs);	
		COControlSensors.save();
	//}

		defs[0] = 0xffff;
		defs[1] = 0xffff;
		COControlDownSockets._setVal(defs);	
		COControlDownSockets.save();
	
		defs[0] = 0xffff;
		defs[1] = 0xffff;
	COControlDownSockets._setVal(defs);	
	COControlDownSockets.save();
	
	//humodity control sensors sockets
	if (humidityControlSensors.undefined())
	{
		
	}
	if (humidityControlUpSockets.undefined())
	{
		
	}
}

