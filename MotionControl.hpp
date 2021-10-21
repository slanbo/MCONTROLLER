#ifndef __MOTION_CONTROL__H
#define __MOTION_CONTROL__H


#include "Control.hpp"
#include "Sensors.hpp"

class MotionControl : public ControlBase
{
public:
	MotionControl(std::string name,
		intTune* onOff,
		intTune* analizeMotionsPeriod,
		std::vector<IRMotionSensor*> &sensors);

	virtual void FillScreen();
	virtual void ExecuteStep();
	virtual bool isActive();
	
	bool active = false;
	
private:
	
	intTune* AnalizeMotionsPeriod;
	std::vector<IRMotionSensor*> &Sensors;
	
protected:
	
};

#endif