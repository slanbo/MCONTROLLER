#include "PCounterControl.hpp"
#include <string.h>
#include "rtc.h"
#include "eeprom.h"
#include "utf8_to_cp1251.h"
#include "Lcd_Driver.h"
#include "GUI.h"
#include "Auxiliary.hpp"
#include "TuneObjectsExt.hpp"
#include "ScreenObjectsExt.hpp"

PCounterControl::PCounterControl(
	std::string name,
	intTune* onOffTune,
	IntVectorTune* socketsTune, 
	intTune*  eepromFirstByte,
	intTune*  eepromSecondByte,
	uint8_t beginHour, 
	uint8_t beginMinute, 
	uint8_t endHour, 
	uint8_t endMinute)
	: SocketsControl(name, onOffTune, nullptr, socketsTune)
	, BeginHour(beginHour)
	, BeginMinute(beginMinute)
	, EndHour(endHour)
	, EndMinute(endMinute)
	, EepromFirstByte(eepromFirstByte)
	, EepromSecondByte(eepromSecondByte)
{

}

void PCounterControl::ExecuteStep()
{
	bool needUpdate = false;
	uint16_t VTToAdd = 0;

	RTC_TimeTypeDef sTime = { 0 };
	RTC_DateTypeDef sDate = { 0 };
	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	
	uint8_t currentHour = sTime.Hours;
	uint8_t currentMinute = sTime.Minutes;

	uint16_t currentMinutes = (currentHour * 60) + currentMinute;
	
	uint16_t beginMinutes = (BeginHour * 60) + BeginMinute;
	uint16_t endMinutes = (EndHour * 60) + EndMinute;
	
	uint16_t endDayMinutes = (23 * 60) + 59;
	
	if (beginMinutes <  endMinutes)
	{
		if (currentMinutes >= beginMinutes & currentMinutes <= endMinutes)
		{
			needUpdate = true;
		}
	}
	else
	{
		if ((currentMinutes >= beginMinutes & currentMinutes <= endDayMinutes) | (currentMinutes >= 1 & currentMinutes <= endMinutes))
		{
			needUpdate = true;
		}
	}
	
	if (needUpdate)
	{
		if (Current_Step_After_FlashWrite < WriteFlashSteps)
		{
			Current_Step_After_FlashWrite += 1;
		}
		else
		{
			Current_Step_After_FlashWrite = 0;
			saveToFlash();
		}
		for (auto sock: SocketsVector)
		{
			if (sock->getSocketState())
			{
				VTToAdd += sock->getLoadpowerVT();
			}
		}
		VT_After_FlashWrite += VTToAdd;
	}
}

void PCounterControl::saveToFlash()
{
	uint32_t VTInHourAFR = getVTHour_After_FlashWrite();
	restoreFromFlash();
	HAL_FLASH_Unlock();
	uint16_t status = EE_Write_Int32(EepromFirstByte->getFlashAddress(), VTInHourAFR + VT_HOUR);
	HAL_FLASH_Lock();
	VT_After_FlashWrite = 0;
}

void PCounterControl::restoreFromFlash()
{
	VT_HOUR = EE_Read_Int32(EepromFirstByte->getFlashAddress());
}

void PCounterControl::FillScreen()
{
	
	char datedevider[] = "/\0";
	char timedevider[] = ":\0";
	char blank[] = " \0";
	
	Info_SubHeader->ClearText();
	Info_FirstString->ClearText();
	Info_SecondString->ClearText();
	Info_ThirdString->ClearText();
	Info_FourthString->ClearText();
	
	Info_SubHeader->SetText(Name, false);
	Info_SubHeader->FillEndBySpaces();
	Info_SubHeader->_setUpdated(true);
	
	char countbeg[] = "Нач. отсчета:";
	Info_FirstString->SetChars(countbeg, true);
	Info_FirstString->FillEndBySpaces();
	Info_FirstString->_setUpdated(true);
	
	Info_SecondString->SetIntText(PCounterBeginDate._getVal(), 2);
	Info_SecondString->SetChars(datedevider, false);
	Info_SecondString->SetIntText(PCounterBeginDate._getVal(), 2);
	Info_SecondString->SetChars(datedevider, false);
	Info_SecondString->SetIntText(PCounterBeginYear._getVal(), 2);
	Info_SecondString->SetChars(blank, false);
	Info_SecondString->SetIntText(PCounterBeginHour._getVal(), 2);
	Info_SecondString->SetChars(timedevider, false);
	Info_SecondString->SetIntText(PCounterBeginMinute._getVal(), 2);
	Info_SecondString->FillEndBySpaces();
	Info_SecondString->_setUpdated(true);
	
	char val[] = "Счетчик:";
	Info_ThirdString->SetChars(val, true);
	Info_ThirdString->FillEndBySpaces();
	Info_ThirdString->_setUpdated(true);
	
	Info_FourthString->SetIntText(VT_HOUR, 10);
	Info_FourthString->FillEndBySpaces();
	Info_FourthString->_setUpdated(true);
	
	getRectCoordinates(Info_Screen, Left_X, Top_Y, Right_X, Bottom_Y);

}

uint32_t PCounterControl::getVTHour_After_FlashWrite()
{
		return (uint32_t)((VT_After_FlashWrite*SecondsInStep) / 3600);
}

uint32_t PCounterControl::getCurrentVtHour()
{
	uint32_t VTHourAFW = getVTHour_After_FlashWrite();
	return VTHourAFW + VT_HOUR;
}