#include "TimeProfile.hpp"
#include "rtc.h"
#include "Auxiliary.h"
#include <string>

DatePeriodValue::DatePeriodValue(
	uint16_t ID,
	std::string name,
	uint8_t variant,
	uint8_t hourBegin, 
	uint8_t minuteBegin, 
	uint8_t hourEnd, 
	uint8_t minuteEnd, 
	uint8_t date, 
	uint8_t weekDay, 
	uint8_t week, 
	uint8_t month, 
	uint8_t year, 
	intTune* tune)
	: PeriodValue(ID, name, tune)
	, Variant(variant)
	, HourBegin(hourBegin)
	, MinuteBegin(minuteBegin)
	, HourEnd(hourEnd)
	, MinuteEnd(minuteEnd)
	, Date(date)
	, WeekDay(weekDay)
	, Week(week)
	, Month(month)
	, Year(year)
{
}

void PeriodValuesCollection::addPeriodValue(PeriodValue* pval)
{
	periodValues.push_back(pval);
}

uint16_t PeriodValuesCollection::getValue(uint8_t variant)
{
	
	if (Type == DATE_PERIOD)
	{
		RTC_TimeTypeDef sTime = { 0 };
		RTC_DateTypeDef sDate = { 0 };
		HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
		HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	
		uint16_t minutesCurrent = sTime.Hours * 60 + sTime.Minutes;
	
		for (auto elem : periodValues)
		{
			DatePeriodValue* pval = (DatePeriodValue*)elem;
			if (
				pval->Date == sDate.Date
				& pval->Month == sDate.Month
				& pval->Year == sDate.Year
				& pval->WeekDay == 0
				& pval->Week == 0
				& pval->Variant == variant)
			{
				uint16_t minutesBegin = pval->HourBegin * 60 + pval->MinuteBegin;
				uint16_t minutesEnd = pval->HourEnd * 60 + pval->MinuteEnd;
				if (minutesCurrent >= minutesBegin & minutesCurrent <= minutesEnd)
				{
						return pval->_getTune()->_getVal();
				}
			}
		}
	
		//find period weekday
		for(auto elem : periodValues)
		{
			DatePeriodValue* pval = (DatePeriodValue*)elem;
			if (
				pval->Date == 0
				& pval->Month == 0
				& pval->Year == 0
				& pval->WeekDay == sDate.WeekDay
				& pval->Week == 0
				& pval->Variant == variant)
			{
				uint16_t minutesBegin = pval->HourBegin * 60 + pval->MinuteBegin;
				uint16_t minutesEnd = pval->HourEnd * 60 + pval->MinuteEnd;
				if (minutesCurrent >= minutesBegin & minutesCurrent <= minutesEnd)
				{
						return pval->_getTune()->_getVal();
				}
			}
		}
	
		//find period eachday
		for(auto elem : periodValues)
		{
			DatePeriodValue* pval = (DatePeriodValue*)elem;
			if (
				pval->Date == 0
				& pval->Month == 0
				& pval->Year == 0
				& pval->WeekDay == 0
				& pval->Week == 0
				& pval->Variant == variant)
			{
				uint16_t minutesBegin = pval->HourBegin * 60 + pval->MinuteBegin;
				uint16_t minutesEnd = pval->HourEnd * 60 + pval->MinuteEnd;
			
				if (minutesCurrent >= minutesBegin & minutesCurrent <= minutesEnd)
				{
						return pval->_getTune()->_getVal();
				}
			}
		}
	}
	else if (Type == TIME_PERIOD)
	{
		for (auto elem : periodValues)
		{
			TimePeriodValue* pval = (TimePeriodValue*)elem;
			if (!pval->Completed())
				return pval->_getTune()->_getVal();
		}
	}
	
	return 0xffff;
}
;

PeriodValuesCollection::PeriodValuesCollection(PeriodType type)
	: Type(type)
{
}


PeriodValue::PeriodValue(uint16_t ID, 
	std::string name, 
	intTune* valTune)
	: BaseObject(ID, name)
	, Tune(valTune)
{
}



intTune* PeriodValue::_getTune()
{
	return Tune;
}


TimePeriodValue::TimePeriodValue(
	uint16_t ID,
	std::string name,
	intTune* tune, 
	intTune* timeTune,
	intTune* stateTune,
	intTune* stayOnTimeTune)
	: PeriodValue(ID, name, tune)
	, TimeTune(timeTune)
	, StateTune(stateTune)
	, StayOnTimeTune(stayOnTimeTune)
{
}


uint16_t TimePeriodValue::getStayOnTime()
{
	return StayOnTimeTune->_getVal();
}

uint16_t TimePeriodValue::getHeatingTime()
{
	return Heating;
}

uint16_t TimePeriodValue::getCoolingTime()
{
	return Cooling;
}

void TimePeriodValue::Reset()
{
	StayOnTimeTune->_setVal(0);
	Heating = 0;
	Cooling = 0;
}

bool TimePeriodValue::Completed()
{
	return StayOnTimeTune->_getVal() >= TimeTune->_getVal();
}

bool TimePeriodValue::isActive()
{
	if (StateTune->_getVal() == 1)
		return true;
	else
		return false;
}

void TimePeriodValue::UpdateStateTime(TimePeriodState state)
{
	if (lastUpdateState == COMPLETED)
		return;
	
	RTC_DateTypeDef dt;
	RTC_TimeTypeDef tt;
	
	HAL_RTC_GetTime(&hrtc, &tt, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &dt, RTC_FORMAT_BIN); 
	
	time_t currentSeconds = getSecondsFromBegin(&dt, &tt);  
	if (lastUpdateSeconds > 0)
	{
		if (state == STAYON & lastUpdateState == STAYON)
		{
			StayOn = StayOn + (currentSeconds - lastUpdateSeconds);
			if (StayOn - StayOnTimeTune->_getVal() >= STAY_ON_WRITE_FLASH_PERIOD) 
			{
				StayOnTimeTune->_setVal(StayOn);
				StayOnTimeTune->save();
			}
			if (StayOn >= TimeTune->_getVal())
				lastUpdateState = COMPLETED;
		}	
		else if (state == HEATING & lastUpdateState == HEATING)
		{
			Heating = Heating + (currentSeconds - lastUpdateSeconds);
		}		
		else if (state == COOLING & lastUpdateState == COOLING)
		{
			Cooling = Cooling + (currentSeconds - lastUpdateSeconds);
		}		
	}
	lastUpdateSeconds = getSecondsFromBegin(&dt, &tt);  
	lastUpdateState = state;
}


void DatePeriodValue::getPeriodDescription(char* descr)
{
	
}


void TimePeriodValue::getPeriodDescription(char* descr)
{
	char CO[3] = { 67, 176, 0};
	
	AddIntChars(descr, Tune->_getVal(), 2, ' ');
	AddChars(descr, " \0", false);
	AddChars(descr, CO, false);
	
	AddIntChars(descr, TimeTune->_getVal(), 4, ' ');
	AddChars(descr, " сек.", false);
}

void TimePeriodValue::getStateDescription(char* descr)
{
	AddIntChars(descr, StayOn, 4, ' ');
	AddChars(descr, " из ", false);
	AddIntChars(descr, TimeTune->_getVal(), 4, ' ');
}



void DatePeriodValue::getStatedDescription(char* descr)
{
	
}

PeriodValue* PeriodValuesCollection::getCurrentPeriod()
{
	if (Type == TIME_PERIOD)
	{
		for (auto elem : periodValues)
		{
			TimePeriodValue* pval = (TimePeriodValue*)elem;
			if (!pval->Completed())
			{
				return elem;
			}
		}
	}
	return nullptr;
	
	
}


bool PeriodValuesCollection::UpdateCurrentperiotStateTime()
{
}
