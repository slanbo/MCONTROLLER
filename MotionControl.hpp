#ifndef __MOTION_CONTROL__H
#define __MOTION_CONTROL__H


#include "Control.hpp"
#include "Sensors.hpp"

class MotionControl : public ControlBase
{
public:
	MotionControl(
		const char* name,
		const char* uid,
		intTune* onOff,
		intTune* analizeMotionsPeriod,
		IntVectorTune* sensorsTune);

	virtual void FillScreen();
	virtual void ExecuteStep();
	virtual bool isActive();
	
	bool active = false;
	
private:
	
	intTune* AnalizeMotionsPeriod;
	
protected:
		std::vector<IRMotionSensor*> Sensors;

};

#endif