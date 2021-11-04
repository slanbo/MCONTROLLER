#ifndef __CONTROL_BASE__H
#define __CONTROL_BASE__H

	
#include "main.h"
#include "Tune.hpp"
#include <string>
#include "BaseObject.hpp"
#include "TimeProfile.hpp"
#include "Socket.hpp"
#include "ADCSensorDev.hpp"

class ControlBase: public BaseObject
{
public:
	
	ControlBase(uint16_t id, std::string name, intTune* onOffTune);
	ControlBase(std::string name, intTune* onOffTune);
	
	char Name[MAX_OBJECT_NAME_LENGHT];
	
	virtual void init(uint8_t index);
	virtual void ExecuteStep() = 0;
	virtual bool isOn();
	virtual bool isActive();
	virtual void FillScreen() = 0;
	void clearLCD();
	
private:
	
protected:
	intTune* OnOffTune;
	uint8_t Left_X = 0;
	uint8_t Top_Y = 0;
	uint8_t Right_X = 0;
	uint8_t Bottom_Y = 0;
	uint16_t BackColor = 0;
};
	
#endif	

class SocketsControl : public ControlBase
{
public:
	SocketsControl
		(
		uint16_t id,
		std::string name,
		intTune* onOffTune,
		IntVectorTune* socketsTune
		);
	
	SocketsControl
		(
		std::string name,
		intTune* onOffTune,
		IntVectorTune* socketsTune
		);
	
private:
	
protected:
	
	IntVectorTune* SocketsTune;
	std::vector< plugSocket*> SocketsVector;
	
};

using createTimeProfileFnc = void(*)(TimeProfile*, intTune*);


class SensorsSocketsControl : public SocketsControl
{
public:
	SensorsSocketsControl(
		uint16_t id,
		std::string name,
		intTune* onOffTune,
		IntVectorTune* sensorsTune,
		IntVectorTune* upSocketsTune,
		IntVectorTune* downSocketsTune,
		intTune* timeProfileTune,
		createTimeProfileFnc ctpFnc
		);
	
	SensorsSocketsControl(
		std::string name,
		intTune* onOffTune,
		IntVectorTune* sensorsTune,
		IntVectorTune* upSocketsTune,
		IntVectorTune* downSocketsTune,
		intTune* timeProfileTune,
		createTimeProfileFnc ctpFnc);
	
	virtual void ExecuteStep();
	virtual void FillScreen();
	virtual bool isActive();
	
	void _fillVector(std::vector<BaseObject*> &vectorOut, std::vector<BaseObject*> &vectorIn, IntVectorTune* tune);
	void SwitchSockets(std::vector< plugSocket*> plugSockets, uint16_t powerVT);
	
	virtual uint16_t _get_aim_val();
	virtual uint16_t _get_current_val();
	
	virtual void _set_aim_val(uint16_t val);
	virtual void _set_current_val(uint16_t val);
	
private:
	
	
protected:
	
	IntVectorTune* SensorsTune;
	IntVectorTune* UpSocketsTune;
	IntVectorTune* DownSocketsTune;
	
	intTune* TimeProfileTune;

	TimeProfile* tProfile;
	
	std::vector< plugSocket*> UpSocketsVector;
	std::vector< plugSocket*> DownSocketsVector;
	std::vector< ADCSensor*> SensorsVector;
	
	uint16_t current_val = 0;
	uint16_t aim_val = 0;
	
};
