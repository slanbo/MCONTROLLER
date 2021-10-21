#include "main.h"
#include "DS18B20.hpp"

#define STAYON_COMPLETED_ADDRESS 0x0700
#define HEATING_COMPLETED_ADDRESS 0x0800
#define COOLING_COMPLETED_ADDRESS 0x0900

class Pause
{
private:
	
	
public:
	Pause(uint8_t Temp, uint16_t TimeSeconds, bool Active);
	bool active = true;
	uint8_t temp = 0;
	uint16_t timeSeconds = 0;
	uint16_t secondsStayOn = 0;
	uint16_t secondsHeating = 0;
	uint16_t secondsCooling = 0;
	bool completed = false;
	
	void addSecondsStayOn(uint16_t sec);
};

class Pauses
{
private:
	
	uint16_t beginStayOnSeconds = 0;
	uint16_t beginHeatingSeconds = 0;
	uint16_t beginCoolingSeconds = 0;
	
	uint8_t currentPause = 0;
	
	uint8_t getAimTemperature();
	void TENSwitch(uint8_t KVT);
	void PUMPSwitch(bool ON);
	void writeMinutesArrayToEEPROM(uint8_t* minutesArray, uint8_t size, uint16_t addr);
	void readMinutesArrayFromEEPROM(uint8_t* minutesArray, uint8_t size, uint16_t addr);
	uint8_t getUncompletedMashingPauseNumber();
	uint8_t getUncompletedBoilingPauseNumber();
	void ConvertMinutesArrayToSecondsArray(uint8_t *pDataIn, uint16_t  *pDataOut, uint16_t Size);
	void ConvertSecondsArrayToMinutesArray(uint16_t *pDataIn, uint8_t *pDataOut, uint16_t Size);
	
	void getPausesScondsStayOnArray(uint16_t* secondsArray, uint8_t size);
	void setPausesScondsStayOnArray(uint16_t* secondsArray, uint8_t size);
	
	void getPausesScondsHeatingArray(uint16_t* secondsArray, uint8_t size);
	void setPausesScondsHeatingArray(uint16_t* secondsArray, uint8_t size);
	
	void getPausesScondsCoolingArray(uint16_t* secondsArray, uint8_t size);
	void setPausesScondsCoolingArray(uint16_t* secondsArray, uint8_t size);

	void readStateFromEEPROM(uint8_t MaxPausesSize);
	void clearStateInEEPROM(uint8_t MaxPausesSize);
	
	DS18B20* sensor;

public:
	
	char Name[16];
	char currentState[16] = "UNDEFENED";
	Pauses(char* pcName, DS18B20* Sensor, Pause* PausesArray, uint8_t MaxPausesSize, bool readEEPROM);
	Pause* pausesArray;
	void Update();
	bool leftSocetSwtched = false;
	bool rightSocetSwtched = false;
	bool socket12VSwitched = false;
	
	uint8_t maxPausesSize;
	
	void fill_CurAimTemp_LCDScreen(i2c_LCD_1602* LcdScreen, uint8_t screenNumber, char* header);
	void fill_State_LCDScreen(i2c_LCD_1602* LcdScreen, uint8_t screenNumber, char* header);
	void fill_Sockets_State_LCDScreen(i2c_LCD_1602* LcdScreen, uint8_t screenNumber, char* header);
		
	
};