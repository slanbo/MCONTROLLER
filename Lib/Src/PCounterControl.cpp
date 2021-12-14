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
	IntVectorTune*  valTune,
	uint8_t beginHour, 
	uint8_t beginMinute, 
	uint8_t endHour, 
	uint8_t endMinute)
	: SocketsControl(name, onOffTune, nullptr, socketsTune)
	, BeginHour(beginHour)
	, BeginMinute(beginMinute)
	, EndHour(endHour)
	, EndMinute(endMinute)
	, ValTune(valTune)
{

}

void PCounterControl::ExecuteStep()
{
	bool date_in_period = false;
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
			date_in_period = true;
	}
	else
	{
		if ((currentMinutes >= beginMinutes & currentMinutes <= endDayMinutes) | (currentMinutes >= 1 & currentMinutes <= endMinutes))
			date_in_period = true;
	}
	
	if (date_in_period)
	{
		time_t curSeconds = getCurrentSecondsFromBegin();
		uint16_t currpower = GetSocketsPowerVT();
		
		if (lastExecuteStepSeconds == 0)
		{
			lastExecuteStepSeconds = curSeconds;
			lastWriteFlashSeconds = curSeconds;
			lastExecuteStepPower = currpower;
			return;
		}
		uint16_t add_vt_hour = 0;
		if (lastExecuteStepPower == currpower)
			VT_Seconds = VT_Seconds + currpower * (curSeconds - lastExecuteStepSeconds);
		
		if (curSeconds - lastWriteFlashSeconds >= WRITE_FLASHE_PERIOD_SECONDS)
		{

			saveToFlash();
			lastWriteFlashSeconds = curSeconds;
			
		}
		lastExecuteStepSeconds = curSeconds;
	}
}

void PCounterControl::saveToFlash()
{
	HAL_FLASH_Unlock();
	uint16_t status = EE_Write_Int64(ValTune->getFlashAddress(), VT_Seconds);
	HAL_FLASH_Lock();
}

void PCounterControl::restoreFromFlash()
{
	VT_Seconds = EE_Read_Int64(ValTune->getFlashAddress());
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
	
	char countbeg[] = "Начало отсчета:";
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
	
	char val[] = "Счетчик ВТ/Ч:";
	Info_ThirdString->SetChars(val, true);
	Info_ThirdString->FillEndBySpaces();
	Info_ThirdString->_setUpdated(true);
	
	Info_FourthString->SetIntText(get_VT_HOUR(), 10);
	Info_FourthString->FillEndBySpaces();
	Info_FourthString->_setUpdated(true);
	
	getRectCoordinates(Info_Screen, Left_X, Top_Y, Right_X, Bottom_Y);
}

uint32_t PCounterControl::get_VT_HOUR()
{
	return (uint32_t)(VT_Seconds / 3600);
}


void PCounterControl::init()
{
	SocketsControl::init();
	restoreFromFlash();
}
