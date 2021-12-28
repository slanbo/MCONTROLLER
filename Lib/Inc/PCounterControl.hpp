#ifndef __PCOUNTER__H
#define __PCOUNTER__H

#include "main.h"
#include "SocketObjectsExt.hpp"
#include "eeprom.h"
#include "vector"
#include "Control.hpp"
#include "time.h"

#define WRITE_FLASHE_PERIOD_SECONDS 60


class PCounterControl : public SocketsControl
{
private:
	uint8_t BeginHour = 0;
	uint8_t BeginMinute = 0;
	uint8_t EndHour = 0;
	uint8_t EndMinute = 0;
	
	IntVectorTune*  ValTune;
	
	time_t lastExecuteStepSeconds = 0;
	time_t lastWriteFlashSeconds = 0;
	uint16_t lastExecuteStepPower = 0;
	
	
	
	
public:
	
	uint32_t get_VT_HOUR();
	
	uint64_t get_VT_Seconds();
	void set_VT_Seconds(uint32_t vthour);
	
	
	uint64_t VT_Seconds = 0;
	
	PCounterControl(
		const char* name,
		const char* uid,
		intTune* onOffTune,
		IntVectorTune* socketsTune, 
		IntVectorTune*  valTune,
		uint8_t beginHour, 
		uint8_t beginMinute, 
		uint8_t endHour, 
		uint8_t endMinute
		);
	
	virtual void ExecuteStep();
	virtual void FillScreen(uint8_t snum);
	void saveToFlash();
	void restoreFromFlash();
	
	virtual void init();
};

#endif













