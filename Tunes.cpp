#include "TuneObjectsExt.hpp"
#include "eeprom.h"
#include "rtc.h"
#include "SocketObjectsExt.hpp"
#include "Auxiliary.hpp"
#include "PauseObjectsExt.hpp"

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
	
	downSocketLoadPower._setVal(18);
	downSocketLoadPower.save();
	
	v12LoadPower._setVal(100);
	v12LoadPower.save();
	
		defs[0] = 1;
		defs[1] = 2;
		PCounterSockets._setVal(defs);	
		PCounterSockets.save();

		
		defs[0] = 2;
		defs[1] = 0xffff;
		airTempControlSensors._setVal(defs);	
		airTempControlSensors.save();
		
		defs[0] = 2;
		defs[1] = 0xffff;
		airTempControlUpSockets._setVal(defs);
		airTempControlUpSockets.save();
	
		defs[0] = 0xffff;
		defs[1] = 0xffff;
		airTempControlDownSockets._setVal(defs);
		airTempControlDownSockets.save();
	
		defs[0] = 3;
		defs[1] = 0xffff;
		batTempControlSensors._setVal(defs);
		batTempControlSensors.save();
	
		defs[0] = 1;
		defs[1] = 0xffff;
		batTempControlUpSockets._setVal(defs);
		batTempControlUpSockets.save();

		defs[0] = 0xffff;
		defs[1] = 0xffff;
		batTempControlDownSockets._setVal(defs);
		batTempControlDownSockets.save();
	
		defs[0] = 4;
		defs[1] = 0xffff;
		lightControlSensors._setVal(defs);	
		lightControlSensors.save();
	
		defs[0] = 0xffff;
		defs[1] = 0xffff;
		lightControlUpSockets._setVal(defs);	
		lightControlUpSockets.save();

		defs[0] = 0xffff;
		defs[1] = 0xffff;
		lightControlDownSockets._setVal(defs);	
		lightControlDownSockets.save();
	
		defs[0] = 1;
		defs[1] = 0xffff;
		COControlSensors._setVal(defs);	
		COControlSensors.save();

		defs[0] = 0xffff;
		defs[1] = 0xffff;
		COControlUpSockets._setVal(defs);	
		COControlUpSockets.save();
	
		defs[0] = 0xffff;
		defs[1] = 0xffff;
		COControlDownSockets._setVal(defs);	
		COControlDownSockets.save();
	
	//beer
	defs[0] = 2;
	defs[1] = 3;
	boilingMashingControlSensors._setVal(defs);	
	boilingMashingControlSensors.save();
	
	defs[0] = 1;
	defs[1] = 0xffff;
	boilingMashingControlUpSockets._setVal(defs);	
	boilingMashingControlUpSockets.save();
	
	defs[0] = 0xffff;
	defs[1] = 0xffff;
	boilingMashingControlDownSockets._setVal(defs);	
	boilingMashingControlDownSockets.save();
	
	beerModeIndex._setVal(0);beerModeIndex.save();	
	PausesVector.at(2)->saveToTunes();
	
	MashingOnOffTune._setVal(1);
	MashingOnOffTune.save();
	
	BoilingOnOffTune._setVal(1);
	BoilingOnOffTune.save();

	PumpOnOffTune._setVal(1); 
	PumpOnOffTune.save();
	
	defs[0] = 2;
	defs[1] = 0xffff;
	pumpControlSockets._setVal(defs);
	pumpControlSockets.save();
		
	PumpMode._setVal(1); 
	PumpMode.save();
		
	SwitchedOnPumpTime._setVal(60); 
	SwitchedOnPumpTime.save();
	
	SwitchedOffPumpTime._setVal(60);
	SwitchedOffPumpTime.save();
	
}

