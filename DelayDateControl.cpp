#include "DelayDateControl.hpp"

DelayDateControl::DelayDateControl(uint16_t id, 
	const char* name, 
	const char* uid,
	intTune* onOffTune, 
	intTune* dateTune, 
	intTune* monthTune, 
	intTune* yearTune, 
	intTune* hourTune, 
	intTune* minuteTune, 
	bool on_off_type)
	: ControlBase(name, uid, onOffTune, nullptr)
	, DateTune(dateTune)
	, MonthTune(monthTune)
	, YearTune(yearTune)
	, HourTune(hourTune)
	, MinuteTune(minuteTune)
	, ON_OFF_type(on_off_type)
{
}

void DelayDateControl::ExecuteStep()
{
	if (isOn())
	{
		compareRes res = CompareDelayAndCurrentDate();
		if (res == MORE | res == EQUAL)
			Active =  !ON_OFF_type;
		else
		{
			Active =  ON_OFF_type;
		}
		
	}
	else
		Active =  !ON_OFF_type;
}

bool DelayDateControl::isActive()
{
	return Active;
}

void DelayDateControl::FillScreen(uint8_t snum)
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
	
	char countbeg[] = "Дата время:";
	Info_FirstString->SetChars(countbeg, true);
	Info_FirstString->FillEndBySpaces();
	Info_FirstString->_setUpdated(true);
	
	Info_SecondString->SetIntText(DateTune->_getVal(), 2);
	Info_SecondString->SetChars(datedevider, false);
	Info_SecondString->SetIntText(MonthTune->_getVal(), 2);
	Info_SecondString->SetChars(datedevider, false);
	Info_SecondString->SetIntText(YearTune->_getVal(), 2);
	Info_SecondString->SetChars(blank, false);
	Info_SecondString->SetIntText(HourTune->_getVal(), 2);
	Info_SecondString->SetChars(timedevider, false);
	Info_SecondString->SetIntText(MinuteTune->_getVal(), 2);
	Info_SecondString->FillEndBySpaces();
	Info_SecondString->_setUpdated(true);
	
	char val[] = "Состояние:";
	Info_ThirdString->SetChars(val, true);
	Info_ThirdString->FillEndBySpaces();
	Info_ThirdString->_setUpdated(true);
	
	if (Active == ON_OFF_type)
		Info_FourthString->SetChars("Активен", true);
	else
		Info_FourthString->SetChars("Ожидание", true);
	
	Info_FourthString->FillEndBySpaces();
	Info_FourthString->_setUpdated(true);
}


bool DelayDateControl::getType()
{
	return ON_OFF_type;
}

compareRes DelayDateControl::CompareDelayAndCurrentDate()
{
	RTC_TimeTypeDef sTime = { 0 };
	RTC_DateTypeDef sDate = { 0 };
	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

	RTC_TimeTypeDef savedTime = { 0 };
	RTC_DateTypeDef savedDate = { 0 };
	
	savedDate.Date = DateTune->_getVal();
	savedDate.Month = MonthTune->_getVal();
	savedDate.Year = YearTune->_getVal();
		
	savedTime.Hours = HourTune->_getVal();
	savedTime.Minutes = MinuteTune->_getVal();	
	savedTime.Seconds = 0;	
		
	compareRes res = CompareDates(&savedDate, &savedTime, &sDate, &sTime);
	
	return res;
	
}

void DelayDateControl::SeveCurrentToDelayDate()
{
	
	RTC_TimeTypeDef sTime = { 0 };
	RTC_DateTypeDef sDate = { 0 };
	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

	
	DateTune->_setVal(sDate.Date); DateTune->save();
	MonthTune->_setVal(sDate.Month); MonthTune->save();
	YearTune->_setVal(sDate.Year); YearTune->save();
	HourTune->_setVal(sTime.Hours); HourTune->save();
	MinuteTune->_setVal(sTime.Minutes); MinuteTune->save();

}
