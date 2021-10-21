#ifndef __TIME_PROFILE_H
#define __TIME_PROFILE_H

#include  "main.h"
#include "TuneObjectsExt.hpp"
#include "BaseObject.hpp"

#define ANTIFROST_TEMP 2

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