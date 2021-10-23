#include "MotionControl.hpp"

MotionControl::MotionControl(std::string name, 
	intTune* onOff, 
	intTune* analizeMotionsPeriod, 
	std::vector<IRMotionSensor*> &sensors)
	: ControlBase(name,  onOff)
	,AnalizeMotionsPeriod(analizeMotionsPeriod)
	, Sensors(sensors)
{
}

void MotionControl::FillScreen()
{
}

void MotionControl::ExecuteStep()
{
	uint16_t analizePeriod = AnalizeMotionsPeriod->_getVal();
	if (OnOffTune->_getVal() == 2)
	{
		for (auto sens : Sensors) 
		{
			if (sens->stepsAfterLastDetection * EXECUTE_STEP_PERIOD_SEC <= analizePeriod)
				active = true;
			else
				active = false;
		}	
	}
}


bool MotionControl::isActive()
{
	return active;
}


