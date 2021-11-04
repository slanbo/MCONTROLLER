#ifndef __MIXCONTROL__H
#define __MIXCONTROL__H

#include "Control.hpp"
#include "SocketObjectsExt.hpp"
#include "Socket.hpp"
#include "TempPause.hpp"
#include "DateControl.hpp"
#include <string>
#include <vector>

class MixControl : public SocketsControl
{
public:
	MixControl(std::string name,
		intTune* onOffTune,
		IntVectorTune* socketsTune,
		intTune * modeTune);
	
	virtual void FillScreen();
	virtual void ExecuteStep();
	bool getState();
	virtual bool isActive();
	
private:
	
	intTune * ModeTune;
	uint16_t stepsSwitchedOn = 0;
	uint16_t stepsSwitchedOff = 0;
};
	

#endif		