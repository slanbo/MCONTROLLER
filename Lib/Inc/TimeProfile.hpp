#ifndef __TIME_PROFILE_H
#define __TIME_PROFILE_H

#include  "main.h"
#include "TuneObjectsExt.hpp"
#include "BaseObject.hpp"
#include <vector>
#include "time.h"



#define ANTIFROST_TEMP 2

enum PeriodType
{
	DATE_PERIOD,
	TIME_PERIOD
};

enum TimePeriodState
{
	HEATING,
	COOLING,
	STAYON,
	NULLSTATE
};

class PeriodValue: public BaseObject
{
private:
public:
	PeriodValue(uint16_t ID, std::string name, uint16_t val);
	PeriodValue(uint16_t ID, std::string name, intTune* valTune);
	
	intTune* _getTune();
	
	
protected:	
	intTune* Tune;
};


class DatePeriodValue : public PeriodValue
{
private:
public:
	
	DatePeriodValue(
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

	
};

class TimePeriodValue : public PeriodValue
{
private:
	
	uint16_t Heating = 0;
	uint16_t Cooling = 0;
	
	intTune* TimeTune;
	intTune* StateTune;
	intTune* StayOnTimeTune;
	
	time_t lastUpdateTime = 0;
	TimePeriodState lastUpdateState = NULLSTATE;
	
public:
	
	TimePeriodValue(
		uint16_t ID,
		std::string name,
		intTune* tune,
		intTune* timeTune,
		intTune* stateTune,
		intTune* stayOnTimeTune);

	void Reset();
	bool Completed();
	
	void setLastUpdateTimeState(TimePeriodState state);

	uint16_t getStayOn();
	void addStayOn(uint16_t val);
	uint16_t getHeating();
	void addHeating(uint16_t val);
	uint16_t getCooling();
	void addCooling(uint16_t val);
	
	bool isActive();

};

class PeriodValuesCollection
{
private:
public:
	
	PeriodValuesCollection(PeriodType Type);
	void addPeriodValue(PeriodValue* pval);
	
	PeriodType Type;
	uint16_t getValue(uint8_t variant);
	std::vector<PeriodValue*> periodValues;
};

#endif 	