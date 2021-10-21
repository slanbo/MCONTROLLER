#include "Pauses.hpp"
#include "math.h"
#include "Settings.hpp"
#include "i2c.h"
#include <string.h>
#include "eeprom.h"
#include "Auxiliary.h"


Pause::Pause(uint8_t Temp, 
	uint16_t TimeSeconds, 
	bool Active)
	: temp(Temp)
	, timeSeconds(TimeSeconds)
	, active(Active)
{
}


Pauses::Pauses(char* pcName, DS18B20* Sensor, Pause* PausesArray, uint8_t MaxPausesSize, bool readEEPROM)
	: sensor(Sensor)
	, pausesArray(PausesArray)
	, maxPausesSize(MaxPausesSize)
{
	for (int i = 0; i < 16 - 1; i++) {
		Name[i] = *pcName;
		if (*pcName == 0)
			break;
		pcName++;
	}
	Name[16 - 1] = 0;
	
	if (readEEPROM)
	{
		readStateFromEEPROM(maxPausesSize);
	}
	else
	{
		clearStateInEEPROM(maxPausesSize);
	}
}

void Pauses::readStateFromEEPROM(uint8_t MaxPausesSize)
{
	uint8_t minutesArray[MaxPausesSize];
	uint16_t secondsArray[MaxPausesSize];
	
	readMinutesArrayFromEEPROM(minutesArray, MaxPausesSize, COOLING_COMPLETED_ADDRESS);
	ConvertMinutesArrayToSecondsArray(minutesArray, secondsArray, MaxPausesSize);
	setPausesScondsCoolingArray(secondsArray, MaxPausesSize);
		
	readMinutesArrayFromEEPROM(minutesArray, MaxPausesSize, HEATING_COMPLETED_ADDRESS);
	ConvertMinutesArrayToSecondsArray(minutesArray, secondsArray, MaxPausesSize);
	setPausesScondsHeatingArray(secondsArray, MaxPausesSize);
	
	readMinutesArrayFromEEPROM(minutesArray, MaxPausesSize, STAYON_COMPLETED_ADDRESS);
	ConvertMinutesArrayToSecondsArray(minutesArray, secondsArray, MaxPausesSize);
	setPausesScondsStayOnArray(secondsArray, MaxPausesSize);

}

void Pauses::clearStateInEEPROM(uint8_t MaxPausesSize)
{
	uint8_t minutesArray[MaxPausesSize];
	for (uint8_t i = 0; i < MaxPausesSize; i++)
	{
		minutesArray[i] = 0;
	}
	
	writeMinutesArrayToEEPROM(minutesArray, MaxPausesSize, COOLING_COMPLETED_ADDRESS);
	writeMinutesArrayToEEPROM(minutesArray, MaxPausesSize, HEATING_COMPLETED_ADDRESS);
	writeMinutesArrayToEEPROM(minutesArray, MaxPausesSize, STAYON_COMPLETED_ADDRESS);

}

uint8_t Pauses::getAimTemperature()
{
	uint8_t aimTemperature = 0;
	for (uint8_t i = 0; i < maxPausesSize; i++)
	{
		if (pausesArray[i].active & !pausesArray[i].completed)
		{
			currentPause = i;
			aimTemperature = pausesArray[i].temp;
			break;
		}
		
	}
	return aimTemperature;
}

void Pauses::getPausesScondsStayOnArray(uint16_t* secondsArray, 
	uint8_t size)
{
	for (uint8_t i = 0; i < size; i++)
	{
		secondsArray[i] = pausesArray[i].secondsStayOn;
	}
}

void Pauses::setPausesScondsStayOnArray(uint16_t* secondsArray, 
	uint8_t size)
{
	for (uint8_t i = 0; i < size; i++)
	{
		 pausesArray[i].addSecondsStayOn(secondsArray[i]);
	}
}

void Pauses::getPausesScondsHeatingArray(uint16_t* secondsArray, 
	uint8_t size)
{
	for (uint8_t i = 0; i < size; i++)
	{
		secondsArray[i] = pausesArray[i].secondsHeating;
	}
}

void Pauses::setPausesScondsHeatingArray(uint16_t* secondsArray, 
	uint8_t size)
{
	for (uint8_t i = 0; i < size; i++)
	{
		pausesArray[i].secondsHeating = secondsArray[i];
	}
}

void Pauses::getPausesScondsCoolingArray(uint16_t* secondsArray, 
	uint8_t size)
{
	for (uint8_t i = 0; i < size; i++)
	{
		secondsArray[i] = pausesArray[i].secondsCooling;
	}
}

void Pauses::setPausesScondsCoolingArray(uint16_t* secondsArray, 
	uint8_t size)
{
	for (uint8_t i = 0; i < size; i++)
	{
		pausesArray[i].secondsCooling = secondsArray[i];
	}
}

void Pauses::Update()
{
	uint8_t pauseAimTemp = getAimTemperature();
	double currentTemp = sensor->ds18b20[0].Temperature;
	
	uint16_t secondsArray[maxPausesSize];
	uint8_t minutesArray[maxPausesSize];
	
	uint32_t seconds = getSeconds();
	
	if (beginCoolingSeconds > 0)
	{
		pausesArray[currentPause].secondsCooling = pausesArray[currentPause].secondsCooling + (seconds - beginCoolingSeconds);
		getPausesScondsCoolingArray(secondsArray, maxPausesSize);
		ConvertSecondsArrayToMinutesArray(secondsArray, minutesArray, maxPausesSize);
		writeMinutesArrayToEEPROM(minutesArray, maxPausesSize, COOLING_COMPLETED_ADDRESS);
	}
	if (beginHeatingSeconds > 0)
	{
		pausesArray[currentPause].secondsHeating = pausesArray[currentPause].secondsHeating + (seconds - beginHeatingSeconds);
		getPausesScondsHeatingArray(secondsArray, maxPausesSize);
		ConvertSecondsArrayToMinutesArray(secondsArray, minutesArray, maxPausesSize);
		writeMinutesArrayToEEPROM(minutesArray, maxPausesSize, HEATING_COMPLETED_ADDRESS);
	}
	if (beginStayOnSeconds > 0)
	{
		pausesArray[currentPause].addSecondsStayOn(seconds - beginStayOnSeconds);
		getPausesScondsStayOnArray(secondsArray, maxPausesSize);
		ConvertSecondsArrayToMinutesArray(secondsArray, minutesArray, maxPausesSize);
		writeMinutesArrayToEEPROM(minutesArray, maxPausesSize, STAYON_COMPLETED_ADDRESS);
	}
	if (currentTemp < pauseAimTemp - 3)
	{
		beginStayOnSeconds = 0;
		beginCoolingSeconds = 0;
		beginHeatingSeconds = seconds;
		
		TENSwitch(3);
		PUMPSwitch(true);
		strcpy(currentState, "HEAT/PUMP");				
	}
	if (currentTemp < pauseAimTemp - 2 & currentTemp >= pauseAimTemp - 3)
	{
		beginStayOnSeconds = 0;
		beginCoolingSeconds = 0;
		beginHeatingSeconds = seconds;
		
		TENSwitch(2);
		PUMPSwitch(true);
		strcpy(currentState, "HEAT/PUMP");				
	}
	if (currentTemp < pauseAimTemp - 1 & currentTemp >= pauseAimTemp - 2)
	{
		beginStayOnSeconds = 0;
		beginCoolingSeconds = 0;
		beginHeatingSeconds = seconds;
		
		TENSwitch(1);
		PUMPSwitch(true);
		strcpy(currentState, "HEAT/PUMP");				
	}
	if (currentTemp < pauseAimTemp & currentTemp >= pauseAimTemp - 1)
	{
		beginStayOnSeconds = seconds;
		beginCoolingSeconds = 0;
		beginHeatingSeconds = 0;
		
		TENSwitch(1);
		PUMPSwitch(true);
		strcpy(currentState, "HEAT/PUMP");				
	}						
						
	if (currentTemp >= pauseAimTemp & currentTemp <= pauseAimTemp + 1)
	{
		beginStayOnSeconds = seconds;
		beginCoolingSeconds = 0;
		beginHeatingSeconds = 0;
		
		TENSwitch(0);
		PUMPSwitch(false);
		strcpy(currentState, "STAY ON");				
	}
			
	if (currentTemp > pauseAimTemp + 1)
	{
		beginStayOnSeconds = 0;
		beginCoolingSeconds = seconds;
		beginHeatingSeconds = 0;
		
		TENSwitch(0);
		PUMPSwitch(true);
		strcpy(currentState, "COOL/PUMP");		
	}
}

void Pauses::ConvertSecondsArrayToMinutesArray(uint16_t *pDataIn, uint8_t *pDataOut, uint16_t Size)
{
	for (uint16_t i = 0; i < Size; i++)
	{
		double mins = pDataIn[i] / 60;
		double out;
		modf(mins, &out);
		pDataOut[i] = out;
	}
}

void Pauses::ConvertMinutesArrayToSecondsArray(uint8_t *pDataIn, uint16_t  *pDataOut, uint16_t Size)
{
	for (uint16_t i = 0; i < Size; i++)
	{
		double seconds = pDataIn[i] * 60;
		double out;
		pDataOut[i] = seconds;
	}
}

void Pauses::TENSwitch(uint8_t KVT)
{
	switch (KVT)
	{
	case 0:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
		leftSocetSwtched = false;
		rightSocetSwtched = false;
		break;
	case 1:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
		leftSocetSwtched = true;
		rightSocetSwtched = false;
		break;
	case 2:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
		leftSocetSwtched = false;
		rightSocetSwtched = true;
		break;
	case 3:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
		leftSocetSwtched = true;
		rightSocetSwtched = true;
		break;
	default:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
		leftSocetSwtched = false;
		rightSocetSwtched = false;
		break;
	}
}

void Pauses::PUMPSwitch(bool ON)
{
	if (ON)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
		socket12VSwitched = true; 
	}
	else
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
		socket12VSwitched = false;		
	}
	
}


void Pauses::writeMinutesArrayToEEPROM(uint8_t* minutesArray, uint8_t size, uint16_t addr)
{
	bool needUpdate = false;
	
	uint8_t pausesMinutesCompletedEEPROM[size];
	//HAL_I2C_Mem_Read(&hi2c1, (uint16_t) I2C1_DEVICE_ADDRESS, addr, sizeof(uint8_t) * 2, pausesMinutesCompletedEEPROM, sizeof(uint8_t) * size, 10);
	for (uint8_t i = 0; i < size; i++)
	{
		if (pausesMinutesCompletedEEPROM[i] != minutesArray[i])
		{
			needUpdate = true;
			break;
		}
	}
	if (needUpdate)
	{
		HAL_StatusTypeDef res; 
		//res = HAL_I2C_IsDeviceReady(&hi2c1, I2C1_DEVICE_ADDRESS, 1, HAL_MAX_DELAY);
		if (res == HAL_OK)                              
		{
			//HAL_I2C_Mem_Write(&hi2c1, (uint16_t) I2C1_DEVICE_ADDRESS, addr, sizeof(uint8_t) * 2, minutesArray, sizeof(uint8_t) * PAUSES, 10);  
		}
	}
	
}

void Pauses::readMinutesArrayFromEEPROM(uint8_t* minutesArray, uint8_t size, uint16_t addr)
{
	
	HAL_StatusTypeDef res; 
	uint8_t clearMinutes[size];
	
	//res = HAL_I2C_IsDeviceReady(&hi2c1, I2C1_DEVICE_ADDRESS, 1, HAL_MAX_DELAY);
	if (res == HAL_OK)                              
	{
	//	HAL_I2C_Mem_Read(&hi2c1, (uint16_t) I2C1_DEVICE_ADDRESS, addr, sizeof(uint8_t) * 2, minutesArray, sizeof(uint8_t) * size, 10);  
	}

	for (uint8_t i = 0; i < size; i++)
	{
		if (minutesArray[i] == 255)
		{
			for (uint8_t i = 0; i < size; i++)
			{
				clearMinutes[i] = 0;
			}
			writeMinutesArrayToEEPROM(clearMinutes, size, addr);
			//HAL_I2C_Mem_Read(&hi2c1, (uint16_t) I2C1_DEVICE_ADDRESS, addr, sizeof(uint8_t) * 2, minutesArray, sizeof(uint8_t) * size, 10);  
			break;
		}
	}
}

void Pause::addSecondsStayOn(uint16_t sec)
{
	secondsStayOn += sec;
	
	if (secondsStayOn > timeSeconds)
	{
		completed = true;
	}
	else
	{
		completed = false;
	}
	
}


void Pauses::fill_CurAimTemp_LCDScreen(
	i2c_LCD_1602* LcdScreen,
	uint8_t screenNumber, 
	char* header)
{
	double curTemperature = sensor->ds18b20[0].Temperature;
	uint8_t aimTemperature = getAimTemperature(); 
	
	strcpy(LcdScreen->screens[screenNumber].FirstString, Name);
	strcat(LcdScreen->screens[screenNumber].FirstString, " t=");
	
	char tmpf[3] = { 0 };
	char tmpd[3] = { 0 };
	double f, s;
	
	f = modf(curTemperature, &s);
	uint8_t d = (uint8_t)(f * 100);
	uint16_t fint = (uint16_t)s;
	inttoabase10(fint, tmpf);
	inttoabase10(d, tmpd);
	
	strcat(LcdScreen->screens[screenNumber].SecondString, tmpf);
	strcat(LcdScreen->screens[screenNumber].SecondString, ".");
	strcat(LcdScreen->screens[screenNumber].SecondString, tmpd);
	
	
	strcat(LcdScreen->screens[screenNumber].SecondString, "AIM t=");
	
	char aimt[3] = { 0 };
	inttoabase10(aimTemperature, aimt);
	strcat(LcdScreen->screens[screenNumber].SecondString, aimt);
}


void Pauses::fill_State_LCDScreen(
	i2c_LCD_1602* LcdScreen,
	uint8_t screenNumber, 
	char* header)
{
	
}


void Pauses::fill_Sockets_State_LCDScreen(
	i2c_LCD_1602* LcdScreen,
	uint8_t screenNumber, 
	char* header)
{
	
}
