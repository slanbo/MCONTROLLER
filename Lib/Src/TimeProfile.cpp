#include "TimeProfile.hpp"
#include "rtc.h"
#include "Auxiliary.hpp"
#include <string>
#include "time.h"

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
			if (!pval->Completed() && pval->isActive())
				return pval->_getTune()->_getVal();
		}
		return 0;
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
	return StayOn;
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
	StayOn  = 0;
	Heating = 0;
	Cooling = 0;
	setState(NULLSTATE);
}

bool TimePeriodValue::Completed()
{
	return StayOn >= TimeTune->_getVal();
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

	time_t currentSeconds =  getCurrentSecondsFromBegin(); // tim
	 
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
			{
				StayOnTimeTune->_setVal(StayOn);
				StayOnTimeTune->save();
				lastUpdateState = COMPLETED;
			}
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
	lastUpdateSeconds = currentSeconds;  
	if (lastUpdateState != COMPLETED)
	lastUpdateState = state;
}


void DatePeriodValue::getPeriodDescription(char* descr)
{
	
}

void DatePeriodValue::getStateDescription(char* descr)
{
	
}

void TimePeriodValue::getPeriodDescription(char* descr)
{
	char CO[3] = { 67, 176, 0};
	
	AddIntChars(descr, Tune->_getVal(), 2, ' ');
	AddChars(descr, " ", false);
	AddChars(descr, CO, false);
	
	AddIntChars(descr, TimeTune->_getVal(), 4, ' ');
	AddChars(descr, " с.", true);
}

void TimePeriodValue::getStateDescription(char* descr)
{
	AddIntChars(descr, StayOn, 4, ' ');
	AddChars(descr, " из ", true);
	AddIntChars(descr, TimeTune->_getVal(), 4, ' ');
}

uint8_t PeriodValuesCollection::getCurrentPeriodIndex()
{
	if (Type == TIME_PERIOD)
	{
		uint8_t i = 0;
		for (auto elem : periodValues)
		{
			TimePeriodValue* pval = (TimePeriodValue*)elem;
			if (!pval->Completed() && pval->isActive())
			{
				return i;
			}
			i++;
		}
	}
	return 0xff;
	
	
}

bool PeriodValuesCollection::UpdateCurrentPeriotStateTime(TimePeriodState state)
{
	if (Type == TIME_PERIOD)
	{
		for (auto elem : periodValues)
		{
			TimePeriodValue* pval = (TimePeriodValue*)elem;
			if (pval->isActive() && pval->getState() != COMPLETED)
			{
				pval->UpdateStateTime(state);
				currentPeriodValue = pval;
				return true;
			}
		}
	}
	currentPeriodValue = nullptr;
	return false;
}

TimePeriodState TimePeriodValue::getState()
{
	return lastUpdateState;
}


void PeriodValuesCollection::RestorePeriodsStates(uint8_t currentT = 0xff)
{
	if (Type == TIME_PERIOD)
	{
		if (currentT == 0xff)
		{
			for (auto elem : periodValues) 
			{
				TimePeriodValue* pval = (TimePeriodValue*)elem;
				pval->Reset();
				pval->StayOnTimeTune->restore();	
				pval->setStayOnTime(pval->StayOnTimeTune->_getVal());
				if (pval->getStayOnTime() >= pval->TimeTune->_getVal())
				{
					pval->setState(COMPLETED);
				}
			}
		}
		else
		{
			for (auto elem : periodValues) 
			{
				TimePeriodValue* pval = (TimePeriodValue*)elem;
				pval->Reset();
				if (pval->Tune->_getVal()  + 3 < currentT)
				{
					pval->setStayOnTime(pval->TimeTune->_getVal());
					pval->setState(COMPLETED);
				}
			}
		}
	}
	
}


void TimePeriodValue::setStayOnTime(uint16_t time)
{
	StayOn = time;
}


void TimePeriodValue::setState(TimePeriodState state)
{
	lastUpdateState  = state;
}


void PeriodValuesCollection::ResetPeriodes()
{
	for (auto elem : periodValues) 
	{
		TimePeriodValue* pval = (TimePeriodValue*)elem;
		pval->Reset();
	}
}


TimePeriodState PeriodValuesCollection::getCurrentState()
{
	if (Type == TIME_PERIOD)
	{
		for (auto elem : periodValues)
		{
			TimePeriodValue* pval = (TimePeriodValue*)elem;
			if (!pval->Completed() && pval->isActive())
			{
				return pval->getState();
			}
		}
	}
	return NULLSTATE;
}


bool PeriodValuesCollection::isActive()
{
	return currentPeriodValue != 0;
}
