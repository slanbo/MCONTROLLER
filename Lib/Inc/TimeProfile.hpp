#ifndef __TIME_PROFILE_H
#define __TIME_PROFILE_H

#include  "main.h"
#include "TuneObjectsExt.hpp"
#include "BaseObject.hpp"
#include <vector>

#define ANTIFROST_TEMP 2




class DatePeriodValue
{
private:
public:
	DatePeriodValue(
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
		uint16_t val);
	
	DatePeriodValue(
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
		intTune* tune);
	
	~DatePeriodValue();
	
	uint8_t Variant;
	uint8_t HourBegin;
	uint8_t MinuteBegin;
	uint8_t HourEnd;
	uint8_t MinuteEnd;
	uint8_t Date;
	uint8_t WeekDay;
	uint8_t Week;
	uint8_t Month;
	uint8_t Year;

	uint16_t val;
	intTune* tune;
};

class DatePeriodValuesCollection
{
private:
public:
	
	DatePeriodValuesCollection();
	
	void addPeriodValue(
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
		);
	
	void addPeriodTune(
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
		);
	
	uint16_t getValue(uint8_t variant);
	std::vector<DatePeriodValue*> periodValues;
};


class TimePeriod
{
private:
	
public:
	
	TimePeriod(uint8_t hourBegin,
				uint8_t minuteBegin,
				uint8_t hourEnd,
				uint8_t minuteEnd,
				uint16_t val);
	
	TimePeriod(uint8_t hourBegin,
				uint8_t minuteBegin,
				uint8_t hourEnd,
				uint8_t minuteEnd,
				intTune* tune);
	
	~ TimePeriod();
	
	uint8_t hourBegin;
	uint8_t minuteBegin;
	uint8_t hourEnd;
	uint8_t minuteEnd;
	uint16_t val;
	bool fromTune;
	intTune* tune;

};

class DayProfile
{
private:
public:
	
	DayProfile(std::vector <TimePeriod*> &timePeriodes);
	~DayProfile();

	std::vector <TimePeriod*> &TimePeriodes;
	uint16_t getVal();
};

class WeekProfile
{
private:
	
public:	
	
	WeekProfile(std::vector<DayProfile*> &dayProfiles);
	~WeekProfile();
	std::vector<DayProfile*> &DayProfiles;
	uint16_t getVal();
	
};

class TimeProfile : public BaseObject
{
private:
public:
	
	TimeProfile(std::string name, WeekProfile* DeaultWeekProfile);
	~TimeProfile();
	WeekProfile* DeaultWeekProfile;
	uint16_t getVal();
	
};

#endif 	