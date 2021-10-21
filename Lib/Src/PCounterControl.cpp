#include "PCounterControl.hpp"
#include <string.h>
#include "rtc.h"
#include "eeprom.h"
#include "utf8_to_cp1251.h"
#include "Lcd_Driver.h"
#include "GUI.h"
#include "Auxiliary.h"
#include "TuneObjectsExt.hpp"
#include "ScreenObjectsExt.hpp"

PCounterControl::PCounterControl(
	std::string name,
	intTune* onOffTune,
	IntVectorTune* socketsTune, 
	uint16_t address, 
	uint8_t beginHour, 
	uint8_t beginMinute, 
	uint8_t endHour, 
	uint8_t endMinute)
	: SocketsControl(name, onOffTune, socketsTune)
	, BeginHour(beginHour)
	, BeginMinute(beginMinute)
	, EndHour(endHour)
	, EndMinute(endMinute)
	, FlashAddress(address)
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
		for (auto sock: Sockets)
		{
			if (sock->getSocketState())
			{
				VTToAdd += sock->loadPowerVT;
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
	uint16_t status = EE_Write_Int32(FlashAddress, VTInHourAFR + VT_HOUR);
	HAL_FLASH_Lock();
	VT_After_FlashWrite = 0;
}

void PCounterControl::restoreFromFlash()
{
	VT_HOUR = EE_Read_Int32(FlashAddress);
}



void PCounterControl::FillScreen()
{
	
	char intString[MAX_CHARS_IN_SCREEN] = { 0 };
	char dateString[MAX_CHARS_IN_SCREEN * 2] = { 0 };
	
	Info_SubHeader.SetText(Name, false);
	Info_FirstString.SetText("Начало отсчета: ", true);
	
	strcpy(dateString, "");
	inttoabase10(PCounterBeginDate._getVal(), intString);
	strcat(dateString, intString);	
	strcat(dateString, "/");
	inttoabase10(PCounterBeginMonth._getVal(), intString);
	strcat(dateString, intString);	
	strcat(dateString, "/");
	inttoabase10(PCounterBeginYear._getVal(), intString);
	strcat(dateString, intString);	
	strcat(dateString, " ");
	inttoabase10(PCounterBeginHour._getVal(), intString);
	strcat(dateString, intString);	
	strcat(dateString, ":");
	inttoabase10(PCounterBeginMinute._getVal(), intString);
	strcat(dateString, intString);	
	Info_SecondString.SetText(dateString, true);
	
	Info_ThirdString.Set_Prefix_IntVal_Postfix_Text("ВТ ЧАС: ", getCurrentVtHour(), 4, "", true);
	Info_FourthString.SetText("", false);
	
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