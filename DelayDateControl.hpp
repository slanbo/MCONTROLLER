#pragma once
#include "Control.hpp"
#include "Auxiliary.hpp"
#include "ScreenObjectsExt.hpp"

class DelayDateControl : public ControlBase
{
public:
	DelayDateControl(
		uint16_t id,
		const char* name,
		intTune* onOffTune,
		intTune* dateTune,
		intTune* monthTune,
		intTune* yearTune,
		intTune* hourTune,
		intTune* minuteTune,
		bool on_off_type
		);
	
	virtual void ExecuteStep();
	virtual bool isActive();
	virtual void FillScreen(uint8_t snum);

	compareRes CompareDelayAndCurrentDate();
	void SeveCurrentToDelayDate();
	
	
	bool getType();

private:
protected:
	
	intTune* DateTune;
	intTune* MonthTune;
	intTune* YearTune;
	intTune* HourTune;
	intTune* MinuteTune;
	
	bool ON_OFF_type;
	
	bool Active;
};





