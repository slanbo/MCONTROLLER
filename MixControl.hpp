#ifndef __MIXPCONTROL__H
#define __MIXPCONTROL__H

#include "Control.hpp"
#include "SocketObjectsExt.hpp"
#include "Socket.hpp"
#include "TempPause.hpp"
#include "DateControl.hpp"
#include <string>
#include <vector>

class MixControl : public ControlBase
{
public:
	MixControl(std::string name,
		intTune* onOffTune,
		std::vector<plugSocket*> &sockets,
		intTune * modeTune,
		std::vector<plugSocket*> &heatingSockets);
	
	virtual void FillScreen();
	virtual void ExecuteStep();
	bool getState();
	virtual bool isActive();
	
private:
	
	intTune * ModeTune;
	uint16_t stepsSwitchedOn = 0;
	uint16_t stepsSwitchedOff = 0;
	std::vector<plugSocket*> &HeatingSockets;
};
	

#endif		