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
		intTune* yearTune,
		intTune* monthTune,
		intTune* dataTune,
		intTune* hourTune,
		intTune* minuteTune
		);

	virtual void FillScreen();
	void ExecuteStep();
	bool isActive();
	bool active = false;
private:
	
	RTC_TimeTypeDef sTime = { 0 };
	RTC_DateTypeDef sDate = { 0 };
	
protected:
	
	intTune *YearTune;
	intTune *MonthTune;
	intTune *DataTune;
	intTune *HourTune;
	intTune *MinuteTune;
	
};

#endif