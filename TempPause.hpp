#ifndef __TEMP_PAUSE__H
#define __TEMP_PAUSE__H

#include "main.h"
#include "Tune.hpp"
#include "NTC_10K_B3950.hpp"
#include "Socket.hpp"
#include "SocketObjectsExt.hpp"
#include "utf8_to_cp1251.h"
#include "Lcd_Driver.h"
#include "GUI.h"
#include "Auxiliary.h"
#include "string.h"	
#include <vector>
	
	class TempPauseTemplate
{
	
public:
	TempPauseTemplate(uint16_t temperature, uint16_t time);
	uint16_t Time;
	uint16_t Temperature;
	char * prefixStr;
};

enum PauseState
{
	INACTIVE,
	HEATING_MAX,
	HEATING_MIN,
	STAY_ON,
	COOLING,
	COMPLETED,
	UNKNOWN
};


class TempPause
{
public:
	TempPause
		(
		uint8_t index,
		IntVectorTune* sensorsTune,
		IntVectorTune* socketsTune
		);
	
	void RenderLCD();
	void FillScreen();
	bool ExecuteStep();
	
	void RestoreTunes();
	PauseState GetState();
	
	void init(std::vector<NTC_10K_B3950*> &termistors,
		std::vector<plugSocket*> &heaterSockets);
	void initTempTime(TempPauseTemplate* tempTime);
	
	uint8_t Index;
	
	TempPauseTemplate* TempTime;
	
	uint16_t Steps_StayOn = 0;
	uint16_t Steps_Heating = 0;
	uint16_t Steps_Cooling = 0;
	
	char Name[40] = "Пауза";
	
	bool active;
	
private:
	
	uint16_t getCurrentTemp();
	void SwitchSockets();
	
	PauseState STATE;
	intTune* TempTune;
	intTune* TimeTune;
	intTune* Time_StayOn_Tune;
	std::vector <NTC_10K_B3950*> &Termistors;
	std::vector <plugSocket*> &HeaterSockets;
	
};
	
#endif