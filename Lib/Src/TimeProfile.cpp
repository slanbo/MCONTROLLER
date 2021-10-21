#include "TimeProfile.hpp"
#include "rtc.h"
#include "Auxiliary.h"
#include <string>

DayProfile::DayProfile(std::vector <TimePeriod*> &timePeriodes)
	: TimePeriodes(timePeriodes)
{
}

DayProfile::~DayProfile()
{
	for (auto timeperiod : TimePeriodes)
		delete timeperiod;
};

uint16_t DayProfile::getVal()
{
	RTC_TimeTypeDef sTime = { 0 };
	RTC_DateTypeDef sDate = { 0 };
	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	
	uint16_t aimVal = 0;
	
	uint8_t hour = sTime.Hours;
	uint8_t minute = sTime.Minutes;
		

	uint16_t minutes = hour * 60 + minute;
	
	for (auto period : TimePeriodes)
	{
		uint8_t beginHour = period->hourBegin;
		uint8_t beginMinute = period->minuteBegin;
		uint16_t beginMinutes = beginHour * 60 + beginMinute;
		
		uint8_t endHour = period->hourEnd;
		uint8_t endMinute = period->minuteEnd;
		uint16_t endMinutes = endHour * 60 + endMinute;
		
		if (minutes >= beginMinutes & minutes <= endMinutes)
		{
			if (period->fromTune)
			{
				aimVal = period->tune->_getVal();
			}
			else
			{
				aimVal = period->val;
			}
			
			break;
		}
		
	}
	if (aimVal != 0)
	{
		return aimVal;
	}
	else
	{
		return 0;
	}
}

TimePeriod::TimePeriod(uint8_t hourBegin, 
	uint8_t minuteBegin, 
	uint8_t hourEnd, 
	uint8_t minuteEnd, 
	uint16_t val
	)
	: hourBegin(hourBegin)
	, minuteBegin(minuteBegin)
	, hourEnd(hourEnd)
	, minuteEnd(minuteEnd)
	, val(val)
{
	fromTune = false;
}

TimePeriod::TimePeriod(uint8_t hourBegin, 
	uint8_t minuteBegin, 
	uint8_t hourEnd, 
	uint8_t minuteEnd, 
	intTune* tune)
	: hourBegin(hourBegin)
	, minuteBegin(minuteBegin)
	, hourEnd(hourEnd)
	, minuteEnd(minuteEnd)
	, tune(tune)
{
	fromTune = true;
}

TimePeriod::~TimePeriod()
{
}

WeekProfile::WeekProfile(std::vector<DayProfile*> &dayProfiles)
	: DayProfiles(dayProfiles)
{
}

WeekProfile::~WeekProfile()
{
	for (auto dayprofile : DayProfiles)
		delete dayprofile;
}

TimeProfile::TimeProfile(std::string name, 
	WeekProfile* deaultWeekTempProfile)
	: BaseObject(name),
	DeaultWeekProfile(deaultWeekTempProfile)
{
}

TimeProfile::~TimeProfile()
{
	delete DeaultWeekProfile;
}

uint16_t TimeProfile::getVal()
{
	
	uint16_t aimTemp = DeaultWeekProfile->getVal();
	return aimTemp;
	
}

uint16_t WeekProfile::getVal()
{

	RTC_TimeTypeDef sTime = { 0 };
	RTC_DateTypeDef sDate = { 0 };
	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	
	//uint8_t dayOfWeek = DS1307_GetDayOfWeek();
	
	uint8_t dayOfWeek = sDate.WeekDay;
	uint16_t aimTemp = DayProfiles[dayOfWeek - 1]->getVal();
	return aimTemp;	
}
