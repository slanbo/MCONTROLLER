#include "TuneObjectsExt.hpp"
#include "eeprom.h"
#include "rtc.h"
#include "SocketObjectsExt.hpp"
#include "Auxiliary.hpp"

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
	
	modeIndex._setVal(1);
	modeIndex.save();
	
	upSocketLoadPower._setVal(1000);
	upSocketLoadPower.save();
	
	downSocketLoadPower._setVal(2000);
	downSocketLoadPower.save();
	
	v12LoadPower._setVal(100);
	v12LoadPower.save();
	
		defs[0] = 2;
		defs[1] = 0xffff;
		airTempControlSensors._setVal(defs);	
		airTempControlSensors.save();
		
		defs[0] = 1;
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
	
		defs[0] = 0;
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
	defs[1] = 2;
	boilingMashingControlUpSockets._setVal(defs);	
	boilingMashingControlUpSockets.save();
	
	defs[0] = 0xffff;
	defs[1] = 0xffff;
	boilingMashingControlDownSockets._setVal(defs);	
	boilingMashingControlDownSockets.save();
	
	beerModeIndex._setVal(1);beerModeIndex.save();
	
	//beer mashing
	mashingPause1Temp._setVal(300);mashingPause1Temp.save();
	mashingPause1Time._setVal(30); mashingPause1Time.save();
	mashingPause1Active._setVal(1); mashingPause1Active.save();
	mashingPause1StayOn._setVal(0); mashingPause1StayOn.save();

	mashingPause2Temp._setVal(300); mashingPause2Temp.save();
	mashingPause2Time._setVal(40); mashingPause2Time.save();
	mashingPause2Active._setVal(1); mashingPause2Active.save();
	mashingPause2StayOn._setVal(0); mashingPause2StayOn.save();
	
	mashingPause3Temp._setVal(300); mashingPause3Temp.save();
	mashingPause3Time._setVal(50); mashingPause3Time.save();
	mashingPause3Active._setVal(1); mashingPause3Active.save();
	mashingPause3StayOn._setVal(0); mashingPause3StayOn.save();
	
	mashingPause4Temp._setVal(300); mashingPause4Temp.save();
	mashingPause4Time._setVal(60); mashingPause4Time.save();
	mashingPause4Active._setVal(1); mashingPause4Active.save();
	mashingPause4StayOn._setVal(0); mashingPause4StayOn.save();
	
	mashingPause5Temp._setVal(300); mashingPause5Temp.save();
	mashingPause5Time._setVal(70); mashingPause5Time.save();
	mashingPause5Active._setVal(1); mashingPause5Active.save();
	mashingPause5StayOn._setVal(0); mashingPause5StayOn.save();
	
	mashingPause6Temp._setVal(300); mashingPause6Temp.save();
	mashingPause6Time._setVal(80); mashingPause6Time.save();
	mashingPause6Active._setVal(0); mashingPause6Active.save();
	mashingPause6StayOn._setVal(0); mashingPause6StayOn.save();
	

	//beer boiling
	boilingPause1Temp._setVal(300); boilingPause1Temp.save();
	boilingPause1Time._setVal(98); boilingPause1Time.save();
	boilingPause1Active._setVal(0); boilingPause1Active.save();
	boilingPause1StayOn._setVal(0); boilingPause1StayOn.save();

	boilingPause2Temp._setVal(300); boilingPause2Temp.save();
	boilingPause2Time._setVal(98); boilingPause2Time.save();
	boilingPause2Active._setVal(0); boilingPause2Active.save();
	boilingPause2StayOn._setVal(0); boilingPause2StayOn.save();

	boilingPause3Temp._setVal(300); boilingPause3Temp.save();
	boilingPause3Time._setVal(98); boilingPause3Time.save();
	boilingPause3Active._setVal(0); boilingPause3Active.save();
	boilingPause3StayOn._setVal(0); boilingPause3StayOn.save();
	
}

