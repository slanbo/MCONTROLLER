#include "PCounterControl.hpp"
//#include <string.h>
#include "rtc.h"
#include "eeprom.h"
#include "utf8_to_cp1251.h"
#include "Lcd_Driver.h"
#include "GUI.h"
#include "Auxiliary.hpp"
#include "TuneObjectsExt.hpp"
#include "ScreenObjectsExt.hpp"

extern SemaphoreHandle_t flashmut_handle;

PCounterControl::PCounterControl(
	const char* name,
	const char* uid,
	intTune* onOffTune,
	IntVectorTune* socketsTune, 
	IntVectorTune*  valTune,
	uint8_t beginHour, 
	uint8_t beginMinute, 
	uint8_t endHour, 
	uint8_t endMinute)
	: SocketsControl(name, uid, onOffTune, nullptr, socketsTune)
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
		{
			VT_Seconds = VT_Seconds + currpower * (curSeconds - lastExecuteStepSeconds);
		}
		lastExecuteStepPower = currpower;
		lastExecuteStepSeconds = curSeconds;

		if (curSeconds - lastWriteFlashSeconds >= WRITE_FLASHE_PERIOD_SECONDS)
		{

			saveToFlash();
			lastWriteFlashSeconds = curSeconds;
			
		}
	}
}

void PCounterControl::saveToFlash()
{
	
	xSemaphoreTake(flashmut_handle, portMAX_DELAY);
	HAL_FLASH_Unlock();
	uint16_t status = EE_Write_Int64(ValTune->getFlashAddress(), VT_Seconds);
	HAL_FLASH_Lock();
	xSemaphoreGive(flashmut_handle);
}

void PCounterControl::restoreFromFlash()
{
	uint64_t clval = 1;

	VT_Seconds = EE_Read_Int64(ValTune->getFlashAddress());
}

void PCounterControl::FillScreen(uint8_t snum)
{
	
	char datedevider[] = "/\0";
	char timedevider[] = ":\0";
	char blank[] = " \0";
	
	Info_SubHeader->ClearText();
	Info_FirstString->ClearText();
	Info_SecondString->ClearText();
	Info_ThirdString->ClearText();
	Info_FourthString->ClearText();
	
	Info_SubHeader->SetChars(Name, false);
	Info_SubHeader->FillEndBySpaces();
	Info_SubHeader->_setUpdated(true);
	
	char countbeg[] = "???????????? ??????????????:";
	Info_FirstString->SetChars(countbeg, true);
	Info_FirstString->FillEndBySpaces();
	Info_FirstString->_setUpdated(true);
	
	Info_SecondString->SetIntText(PCounterBeginDate._getVal(), 2);
	Info_SecondString->SetChars(datedevider, false);
	Info_SecondString->SetIntText(PCounterBeginMonth._getVal(), 2);
	Info_SecondString->SetChars(datedevider, false);
	Info_SecondString->SetIntText(PCounterBeginYear._getVal(), 2);
	Info_SecondString->SetChars(blank, false);
	Info_SecondString->SetIntText(PCounterBeginHour._getVal(), 2);
	Info_SecondString->SetChars(timedevider, false);
	Info_SecondString->SetIntText(PCounterBeginMinute._getVal(), 2);
	Info_SecondString->FillEndBySpaces();
	Info_SecondString->_setUpdated(true);
	
	char val[] = "?????????????? ????/??:";
	Info_ThirdString->SetChars(val, true);
	Info_ThirdString->FillEndBySpaces();
	Info_ThirdString->_setUpdated(true);
	
	Info_FourthString->SetIntText(get_VT_HOUR(), 10);
	Info_FourthString->FillEndBySpaces();
	Info_FourthString->_setUpdated(true);
	
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


void PCounterControl::set_VT_Seconds(uint32_t val)
{
	VT_Seconds = val;
}

uint64_t PCounterControl::get_VT_Seconds()
{
	return VT_Seconds;
}
