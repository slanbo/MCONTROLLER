#include "DateControl.hpp"
#include "rtc.h"
#include "time.h"
#include "Auxiliary.hpp"
#include "ScreenObjectsExt.hpp"
#include "string.h"


void DateControl::FillScreen()
{
	Info_SubHeader->SetText(Name, false);
	
	char statestr[MAX_CHARS_IN_SCREEN] = { 0 };
	strcpy(statestr, "Сост:");
	if (active == true)
	strcat(statestr, "АКТИВЕН");
	else
	strcat(statestr, "ОЖИДАНИЕ");
	Info_FirstString->SetText(statestr, true);
	Info_SecondString->SetText("Дата:", true);
	
	char datestring[MAX_CHARS_IN_SCREEN] = { 0 };
	char intstring[MAX_CHARS_IN_SCREEN] = { 0 };
	
	strcpy(datestring, "");
	inttoabase10(DataTune->_getVal(), intstring);
	strcat(datestring, intstring);	
	strcat(datestring, "/");
	inttoabase10(MonthTune->_getVal(), intstring);
	strcat(datestring, intstring);	
	strcat(datestring, "/");
	inttoabase10(YearTune->_getVal(), intstring);
	strcat(datestring, intstring);	
	strcat(datestring, " ");
	inttoabase10(HourTune->_getVal(), intstring);
	strcat(datestring, intstring);	
	strcat(datestring, ":");
	inttoabase10(MinuteTune->_getVal(), intstring);
	strcat(datestring, intstring);	
	Info_ThirdString->SetText(datestring, true);
	Info_FourthString->SetText("", false);
	
	getRectCoordinates(Info_Screen, Left_X, Top_Y, Right_X, Bottom_Y);

}

void DateControl::ExecuteStep()
{
	RTC_DateTypeDef storedDate = { 0 };
	storedDate.Year = YearTune->_getVal() - 2000;
	storedDate.Month = MonthTune->_getVal() ;
	storedDate.Date = DataTune->_getVal();

	RTC_TimeTypeDef storedTime = { 0 };
	storedTime.Hours = HourTune->_getVal();
	storedTime.Minutes = MinuteTune->_getVal();
	
	RTC_DateTypeDef sDate = { 0 };
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	RTC_TimeTypeDef sTime = { 0 };
	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	
	compareRes res = CompareDates(&sDate, &sTime, &storedDate, &storedTime);
	
	if (res == LESS)
		active = false;
	else
		active = true;
}



DateControl::DateControl(std::string name, 
	intTune* onOff, 
	intTune* yearTune,
	intTune* monthTune,
	intTune* dataTune,
	intTune* hourTune,
	intTune* minuteTune) 
	: ControlBase(name, onOff, nullptr)
	, YearTune(yearTune)
	
{
	
}

bool DateControl::isActive()
{
	bool retActive;
	if (isOn())
		return active;
	else
		return false;
}


