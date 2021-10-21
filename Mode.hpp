#ifndef __MODE__H
#define __MODE__H

#include "main.h"
#include "Tune.hpp"
#include <string>
#include <vector>
#include "Control.hpp"
#include "BaseObject.hpp"

#define MODE_HEADER_BOARD_GAP 2


class ModeBase : public BaseObject
{
public:
	
	ModeBase(uint16_t ID, std::string name);
	
	virtual void FillScreen() = 0;
	virtual void ExecuteStep() = 0;
	
	virtual bool isActive();
	
	virtual void init(uint8_t index);
	
private:
protected:
	
	char Name[MAX_OBJECT_NAME_LENGHT];
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
	
protected:	
	//std::vector<ControlBase *> Controls;
};


class Habitat : public ControlsMode
{
	public: 
	Habitat(uint16_t ID, std::string name);
	~Habitat();
	
	
protected:
	
	TempControl* airTempControl;
	TempControl* batTempControl;
	LightControl* lightControl;
	COControl* coControl;
	
	
	
};

class Drying : public ControlsMode
{
	
};

class BeerPreparing : public ControlsMode
{
	
};

#endif