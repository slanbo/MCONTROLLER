#ifndef __PCOUNTER__H
#define __PCOUNTER__H

#include "main.h"
#include "SocketObjectsExt.hpp"
#include "eeprom.h"
#include "vector"
#include "Control.hpp"

class PCounterControl : public SocketsControl
{
private:
	uint8_t BeginHour = 0;
	uint8_t BeginMinute = 0;
	uint8_t EndHour = 0;
	uint8_t EndMinute = 0;
	intTune*  EepromFirstByte;
	intTune*  EepromSecondByte;
	uint16_t WriteFlashSteps = 60;
	uint16_t Current_Step_After_FlashWrite = 0;
	uint32_t VT_After_FlashWrite = 0;
	uint16_t SecondsInStep = 1;
	uint32_t getVTHour_After_FlashWrite();
	uint32_t getCurrentVtHour();
	
public:
	
	char Name[MAX_OBJECT_NAME_LENGHT];
	
	uint32_t VT_HOUR = 0;
	
	PCounterControl(std::string pcName,
		intTune* onOffTune,
		IntVectorTune* socketsTune, 
		intTune*  eepromFirstByte,
		intTune*  eepromSecondByte,
		uint8_t beginHour, 
		uint8_t beginMinute, 
		uint8_t endHour, 
		uint8_t endMinute
		);
	
	virtual void ExecuteStep();
	virtual void FillScreen();
	void saveToFlash();
	void restoreFromFlash();
	
	
};

#endif













