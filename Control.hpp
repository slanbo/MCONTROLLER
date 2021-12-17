#ifndef __CONTROL_BASE__H
#define __CONTROL_BASE__H

	
#include "main.h"
#include "Tune.hpp"
//#include <string>
#include "BaseObject.hpp"
#include "TimeProfile.hpp"
#include "Socket.hpp"
#include "ADCSensorDev.hpp"

enum socketsState
{
	INCREASEMAX,
	INCREASEMID,
	INCREASEMIN,
	STAYONAIM,
	DECREASEMIN,
	DECREASEMID,
	DECREASEMAX
};


class ControlBase: public BaseObject
{
public:
	ControlBase();
	
	ControlBase(uint16_t id,
		const char* name,
		intTune* onOffTune,
		intTune* switchOnMotionPeriodTune);
	
	ControlBase(const char* name,
		intTune* onOffTune,
		intTune* switchOnMotionPeriodTune);
	
	virtual void init();
	virtual void ExecuteStep() = 0;
	virtual bool isOn();
	virtual void setOn(bool state);
	virtual bool isActive();
	virtual void FillScreen() = 0;
	void clearLCD();
	
private:
	
protected:
	intTune* OnOffTune;
	intTune* SwitchOnMotionPeriodTune;
	uint8_t Left_X = 0;
	uint8_t Top_Y = 0;
	uint8_t Right_X = 0;
	uint8_t Bottom_Y = 0;
	uint16_t BackColor = 0;
};
	

class SocketsControl : public ControlBase
{
public:
	SocketsControl();
	
	SocketsControl
		(
		uint16_t id,
		const char* name,
		intTune* onOffTune,
		intTune* switchOnMotionPeriodTune,
		IntVectorTune* socketsTune
		);
	
	SocketsControl
		(
		const char* name,
		intTune* onOffTune,
		intTune* switchOnMotionPeriodTune,
		IntVectorTune* socketsTune
		);
	
	void SwitchSockets(uint16_t powerVT);
	uint16_t GetSocketsPowerVT();
	
	virtual void init();
	socketsState SocketsState;
	
	
private:
	
protected:
	
	void SwitchToPower(std::vector< plugSocket*> &sockets, uint16_t powerVT);
	
	
	IntVectorTune* SocketsTune;
	std::vector< plugSocket*> SocketsVector;
	
};


class SensorsSocketsControl : public SocketsControl
{
public:
	SensorsSocketsControl();
	
	SensorsSocketsControl(
		uint16_t id,
		const char* name,
		intTune* onOffTune,
		intTune* switchOnMotionPeriodTune,
		IntVectorTune* sensorsTune,
		IntVectorTune* upSocketsTune,
		IntVectorTune* downSocketsTune,
		intTune* timeProfileTune,
		PeriodValuesCollection* dpvcollection
		);
	
	SensorsSocketsControl(
		const char* name,
		intTune* onOffTune,
		intTune* switchOnMotionPeriodTune,
		IntVectorTune* sensorsTune,
		IntVectorTune* upSocketsTune,
		IntVectorTune* downSocketsTune,
		intTune* timeProfileTune,
		PeriodValuesCollection* dpvcollection);
	
	~SensorsSocketsControl();
	
	virtual void ExecuteStep();
	virtual void FillScreen();
	
	virtual uint16_t _get_aim_val();
	virtual uint16_t _get_current_val();
	
	virtual void _set_aim_val(uint16_t val);
	virtual void _set_current_val(uint16_t val);
	
	virtual char* GetSensorsUnit();
	
	uint16_t GetDownSocketsPowerVT();
	void SwitchDownSockets(uint16_t powerVT);
	
	PeriodValuesCollection* DPVCollection = nullptr;
	
	virtual void init();


private:
	
	
protected:
	
	IntVectorTune* SensorsTune = nullptr;
	IntVectorTune* DownSocketsTune = nullptr;
	intTune* TimeProfileTune = nullptr;

	std::vector< plugSocket*> DownSocketsVector;
	std::vector< ADCSensor*> SensorsVector;
	
	uint16_t current_val = 0;
	uint16_t aim_val = 0;
	
};

class PumpControl : public SocketsControl
{
public:
	PumpControl(uint16_t id,
		const char* name,
		intTune* onOffTune,
		IntVectorTune* SocketsTune,
		intTune* pumpModeTune,
		intTune* periodOnTune,
		intTune* periodOffTune,
		PeriodValuesCollection* dpvcollection);
		
	virtual void ExecuteStep();
	virtual void FillScreen();

	
protected:
	intTune* PumpModeTune;
	intTune* PeriodOnTune;
	intTune* PeriodOffTune;
	PeriodValuesCollection* DPVCollection;

	time_t swichedSeconds = 0;
};

#endif	
