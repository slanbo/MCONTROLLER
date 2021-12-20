#ifndef __MODE__H
#define __MODE__H

#include "main.h"
#include "Tune.hpp"
//#include <string>
#include <vector>
#include "Control.hpp"
#include "BaseObject.hpp"
#include "ScreenObjectsExt.hpp"
#include "TimeProfileObjectsExt.hpp"


#define MODE_HEADER_BOARD_GAP 2
#define BEER_PREPARING_SCREEN_QUANT 3


class ModeBase : public BaseObject
{
public:
	
	ModeBase(uint16_t ID, const char* name);
	
	virtual void FillScreen() = 0;
	virtual void ExecuteStep() = 0;
	virtual void init() = 0;
	
	virtual bool isOn() = 0;
	virtual bool isActive() = 0;
	
	bool allscreensfilled = false;
	
private:
protected:
	
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
	ControlsMode(uint16_t ID, const char* name);
	
	virtual void FillScreen();
	virtual void ExecuteStep();
	virtual void init();
	virtual bool isOn();
	virtual bool isActive();
	
	std::vector<SocketsControl*> controlsVector;

protected:	
	uint8_t currentControlIndex = 0;
};

class Habitat : public ControlsMode
{
	public: 
	Habitat(uint16_t ID, const char* name);
	virtual void init();

	SensorsSocketsControl* airTempControl;
	SensorsSocketsControl* batTempControl;
	SensorsSocketsControl* lightControl;
	SensorsSocketsControl* coControl;
	

	
	~Habitat();
	
	protected:
	private:
	
};


class BeerPreparing : public ControlsMode
{
public: 
	BeerPreparing(uint16_t ID,
		const char* name);
	virtual void init();

	SensorsSocketsControl* mashingControl;
	SensorsSocketsControl* boilingControl;
	
	PumpControl* pumpControl;
	
	virtual void ExecuteStep();

	
	~BeerPreparing();
	
protected:
	uint8_t currentScreenIndex = 0;

	
private:
};


class Drying : public ControlsMode
{
public: 
	Drying(uint16_t ID, const char* name);
	virtual void init();

	SensorsSocketsControl* airTempControl;
	SensorsSocketsControl* humidityControl;
	
	~Drying();
	
protected:
private:
	
};

class GreenHouse : public ControlsMode
{
public: 
	GreenHouse(uint16_t ID, const char* name);
	virtual void init();

	SensorsSocketsControl* airTempControl;
	SensorsSocketsControl* humidityControl;
	SensorsSocketsControl* lightControl;
	
	
	~GreenHouse();
	
protected:
private:
	
};





#endif