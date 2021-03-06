#ifndef __TIME_PROFILE_H
#define __TIME_PROFILE_H

#include  "main.h"
#include "TuneObjectsExt.hpp"
#include "BaseObject.hpp"
#include <vector>
#include "time.h"
#include "Tune.hpp"



#define ANTIFROST_TEMP 2
#define STAY_ON_WRITE_FLASH_PERIOD 60

enum ValueType
{
	LOW_LEVEL,
	HIGH_LEVEL
};

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
	PeriodValue(uint16_t ID, const char* name, uint16_t val);
	PeriodValue(uint16_t ID, const char* name, intTune* lowLevelTune, intTune* highLevelTune);
	
	intTune* _getLowLevelTune();
	intTune* _getHighLevelTune();
		
	intTune* LowLevelTune;
	intTune* HighLevelTune;
	
	
protected:	
};


class DatePeriodValue : public PeriodValue
{
private:
public:
	
	DatePeriodValue(
		uint16_t ID,
		const char* name,
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
		intTune* lowLeveltune,
		intTune* highLeveltune);
	
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
	uint16_t StayOn = 0;

	
	intTune* StateTune;
	
	time_t lastUpdateSeconds = 0;
	TimePeriodState lastUpdateState = NULLSTATE;
	
	
public:
	
	TimePeriodValue(
		uint16_t ID,
		const char* name,
		intTune* lowleveltune,
		intTune* highleveltune,
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
	

	intTune* StayOnTimeTune;
	intTune* TimeTune;

};

class PeriodValuesCollection
{
private:
	
public:
	
	PeriodValuesCollection(std::vector<PeriodValue*>& periodValues);
	PeriodValuesCollection(std::vector<PeriodValue*>& periodValues, intTune* stayOnDeltaTune);
	
	
	PeriodType Type;
	uint16_t getValue(ValueType type, uint8_t variant);
	std::vector<PeriodValue*>& PeriodValues;
	
	uint8_t getCurrentPeriodIndex();
	
	TimePeriodState getCurrentState();
	
	bool isActive();
	
	bool UpdateCurrentPeriotStateTime(TimePeriodState state);
	
	void RestorePeriodsStates(uint8_t currentT);
	
	void ResetPeriodes();

	void SetBeforePausesCompleted(uint16_t pauseNum);
	
	PeriodValue* currentPeriodValue = nullptr;
	
	intTune* StayOnDeltaTune;

};

#endif 	