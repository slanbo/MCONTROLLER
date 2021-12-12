#ifndef __TIME_PROFILE_H
#define __TIME_PROFILE_H

#include  "main.h"
#include "TuneObjectsExt.hpp"
#include "BaseObject.hpp"
#include <vector>
#include "time.h"



#define ANTIFROST_TEMP 2
#define STAY_ON_WRITE_FLASH_PERIOD 120

enum PeriodType
{
	DATE_PERIOD,
	TIME_PERIOD
};

enum TimePeriodState
{
	COMPLETED,
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
	
	virtual void getPeriodDescription(char* descr) = 0;
	virtual void getStateDescription(char* descr) = 0;
	
	intTune* Tune;
	
protected:	
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
	
	virtual void getPeriodDescription(char* descr);
	virtual void getStateDescription(char* descr);

	
};

class TimePeriodValue : public PeriodValue
{
private:
	
	uint16_t Heating = 0;
	uint16_t Cooling = 0;
	uint16_t StayOn = 0;

	
	intTune* StateTune;
	
	time_t lastUpdateSeconds = 0;
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
	
	void UpdateStateTime(TimePeriodState state);
	
	uint16_t getStayOnTime();
	void setStayOnTime(uint16_t time);
	
	uint16_t getHeatingTime();
	uint16_t getCoolingTime();
	
	TimePeriodState  getState();
	void  setState(TimePeriodState state);
	
	bool isActive();
	
	virtual void getPeriodDescription(char* descr);
	virtual void getStateDescription(char* descr);

	intTune* StayOnTimeTune;
	intTune* TimeTune;
	
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
	
	PeriodValue* getCurrentPeriod();
	
	TimePeriodState getCurrentState();
	
	
	bool UpdateCurrentPeriotStateTime(TimePeriodState state);
	
	void RestorePeriodsStates(uint8_t currentT);
	
	void ResetPeriodes();

	
};

#endif 	