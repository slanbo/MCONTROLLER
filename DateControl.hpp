#ifndef __DATE_CONTROL__H
#define __DATE_CONTROL__H


#include "Control.hpp"
#include "Tune.hpp"

class DateControl : public ControlBase
{
public:
	DateControl
		(
		std::string name,
		intTune* onOff,
		DateTune* yearTune,
		DateTune* monthTune,
		DateTune* dataTune,
		DateTune* hourTune,
		DateTune* minuteTune,
		DateTune* secondsTune
		);

	virtual void FillScreen();
	void ExecuteStep();
	bool isActive();
	bool active = false;
private:
	
	RTC_TimeTypeDef sTime = { 0 };
	RTC_DateTypeDef sDate = { 0 };
	
protected:
	
	DateTune *YearTune;
	DateTune *MonthTune;
	DateTune *DataTune;
	DateTune *HourTune;
	DateTune *MinuteTune;
	DateTune *SecondsTune;
	
};

#endif