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

DatePeriodValue::DatePeriodValue(
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
	uint16_t val)
	: Variant(variant)
	, HourBegin(hourBegin)
	, MinuteBegin(minuteBegin)
	, HourEnd(hourEnd)
	, MinuteEnd(minuteEnd)
	, Date(date)
	, WeekDay(weekDay)
	, Week(week)
	, Month(month)
	, Year(year)
	, val(val)
	, tune()
{
}

DatePeriodValue::DatePeriodValue(
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
	: Variant(variant)
	, HourBegin(hourBegin)
	, MinuteBegin(minuteBegin)
	, HourEnd(hourEnd)
	, MinuteEnd(minuteEnd)
	, Date(date)
	, WeekDay(weekDay)
	, Week(week)
	, Month(month)
	, Year(year)
	, tune(tune)
{
	
}

void DatePeriodValuesCollection::addPeriodValue
	(
	uint8_t Variant,
	uint8_t HourBegin, 
	uint8_t MinuteBegin, 
	uint8_t HourEnd, 
	uint8_t MinuteEnd, 
	uint8_t Date, 
	uint8_t WeekDay, 
	uint8_t Week, 
	uint8_t Month, 
	uint8_t Year, 
	uint8_t val
	)
{
	DatePeriodValue* pval = new DatePeriodValue(
		Variant,
		HourBegin, 
		MinuteBegin, 
		HourEnd, 
		MinuteEnd, 
		Date, 
		WeekDay, 
		Week, 
		Month, 
		Year, 
		val);
	
	periodValues.push_back(pval);
}


void DatePeriodValuesCollection::addPeriodTune
	(
	uint8_t Variant,
	uint8_t HourBegin, 
	uint8_t MinuteBegin, 
	uint8_t HourEnd, 
	uint8_t MinuteEnd, 
	uint8_t Date, 
	uint8_t WeekDay, 
	uint8_t Week, 
	uint8_t Month, 
	uint8_t Year, 
	intTune* tune
	)
{
	DatePeriodValue* pval = new DatePeriodValue(
		Variant,
		HourBegin, 
		MinuteBegin, 
		HourEnd, 
		MinuteEnd, 
		Date, 
		WeekDay, 
		Week, 
		Month, 
		Year, 
		tune
		);
	
	pval->val = 0xffff;
	periodValues.push_back(pval);
}

uint16_t DatePeriodValuesCollection::getValue(uint8_t variant)
{
	RTC_TimeTypeDef sTime = { 0 };
	RTC_DateTypeDef sDate = { 0 };
	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	
	uint16_t retVal = 0xffff;
	
	DatePeriodValue* foundpval = nullptr;
	
	
	for(auto pval : periodValues)
	{
		if (
			pval->Date == sDate.Date
			& pval->Month == sDate.Month
			& pval->Year == sDate.Year
			& pval->WeekDay == 0
			& pval->Week == 0
			& pval->Variant == variant
			)
		{
			foundpval = pval;
			break;
		}
	}
	
	//find period weekday
	if (foundpval == nullptr)
	for(auto pval : periodValues)
	{
		if (
			pval->Date == 0
			& pval->Month == 0
			& pval->Year == 0
			& pval->WeekDay == sDate.WeekDay
			& pval->Week == 0
			& pval->Variant == variant
			)
		{
			foundpval = pval;
			break;
		}
	}
	
	//find period eachday
	if(foundpval == nullptr)
	for(auto pval : periodValues)
	{
		if (
			pval->Date == 0
			& pval->Month == 0
			& pval->Year == 0
			& pval->WeekDay == 0
			& pval->Week == 0
			& pval->Variant == variant
			)
		{
			foundpval = pval;
			break;
		}
	}
	
	if (foundpval != nullptr)
	{
		uint16_t minutesCurrent = sTime.Hours * 60 + sTime.Minutes;
		uint16_t minutesBegin = foundpval->HourBegin * 60 + foundpval->MinuteBegin;
		uint16_t minutesEnd = foundpval->HourEnd * 60 + foundpval->MinuteEnd;
			
		if (minutesCurrent >= minutesBegin & minutesCurrent <= minutesEnd)
		{
			if (foundpval->val == 0xffff)
				retVal = foundpval->tune->_getVal();
			else
				retVal = foundpval->val;
		}	
	}
	return retVal;
};



DatePeriodValuesCollection::DatePeriodValuesCollection()
{
}
