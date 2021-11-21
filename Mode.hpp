#ifndef __MODE__H
#define __MODE__H

#include "main.h"
#include "Tune.hpp"
#include <string>
#include <vector>
#include "Control.hpp"
#include "BaseObject.hpp"
#include "ScreenObjectsExt.hpp"
#include "TimeProfileObjectsExt.hpp"


#define MODE_HEADER_BOARD_GAP 2


class ModeBase : public BaseObject
{
public:
	
	ModeBase(uint16_t ID, std::string name);
	
	virtual void FillScreen() = 0;
	virtual void ExecuteStep() = 0;
	virtual void init() = 0;
	virtual bool isActive() = 0;
	
	
private:
protected:
	
	uint8_t Index = 0;
	intTune* ModeTune;
	
	uint8_t Left_X = 0;
	uint8_t Top_Y = 0;
	uint8_t Right_X = 0;
	uint8_t Bottom_Y = 0;
	uint16_t BackColor = 0;
};

class ControlsMode : public ModeBase
{
public:
	ControlsMode(uint16_t ID, std::string name);
	
	virtual void FillScreen();
	virtual void ExecuteStep();
	virtual void init();
	
protected:	
	std::vector<ControlBase *> Controls;
};

class Habitat : public ControlsMode
{
	public: 
	Habitat(uint16_t ID, std::string name);
	virtual void FillScreen();
	virtual void ExecuteStep();
	virtual void init();
	virtual bool isActive();
	
	SensorsSocketsControl* airTempControl;
	SensorsSocketsControl* batTempControl;
	SensorsSocketsControl* lightControl;
	SensorsSocketsControl* coControl;
	
	std::vector<SocketsControl*> controlsVector = { airTempControl };

	
	//~Habitat();
	
	protected:
	
	
	private:
	
	uint8_t currentControlIndex = 0;
};

class Drying : public ControlsMode
{
	
};

class BeerPreparing : public ControlsMode
{
	
};
#endif