#include "MotionControl.hpp"
#include "SensorObjectsExt.hpp"

MotionControl::MotionControl(std::string name, 
	intTune* onOff, 
	intTune* analizeMotionsPeriod, 
	IntVectorTune* sensorsTune)
	: ControlBase(name,  onOff, nullptr),
	AnalizeMotionsPeriod(analizeMotionsPeriod)
{
	Sensors.clear();
	for (auto inItem : IRMotionSensorsV)
		for (auto tuneval : sensorsTune->val)
			if (tuneval == inItem->_getId())
				Sensors.push_back(inItem);

	
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


