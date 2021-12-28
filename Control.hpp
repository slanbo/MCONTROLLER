#ifndef __CONTROL_BASE__H
#define __CONTROL_BASE__H

	
#include "main.h"
#include "Tune.hpp"
#include "BaseObject.hpp"
#include "TimeProfile.hpp"
#include "Socket.hpp"
#include "ADCSensorDev.hpp"

#define MAX_UID_LENGHT 16

enum aimValSupportType
{
	ON_BORDERS,
	IN_BORDERS,
	ON_CENTER
};

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
		const char* uid,
		intTune* onOffTune,
		intTune* switchOnMotionPeriodTune);
	
	ControlBase(
		const char* name,
		const char* uid,
		intTune* onOffTune,
		intTune* switchOnMotionPeriodTune);
	
	virtual void init();
	virtual void ExecuteStep() = 0;
	virtual bool isOn();
	virtual void setOn(bool state);
	virtual bool isActive();
	virtual void FillScreen(uint8_t snum) = 0;
	
	virtual void GetUsartMessage(uint8_t messagenum);
	
	uint8_t getScreensQuant();
	
private:
	
protected:
	char UID[MAX_UID_LENGHT];
	
	intTune* OnOffTune;
	intTune* SwitchOnMotionPeriodTune;
	uint8_t screensQuant = 1;
};
	
class SocketsControl : public ControlBase
{
public:
	SocketsControl();
	
	SocketsControl
		(
		uint16_t id,
		const char* name,
		const char* uid,
		intTune* onOffTune,
		intTune* switchOnMotionPeriodTune,
		IntVectorTune* socketsTune
		);
	
	SocketsControl
		(
		const char* name,
		const char* uid,
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
		const char* uid,
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
		const char* uid,
		intTune* onOffTune,
		intTune* switchOnMotionPeriodTune,
		IntVectorTune* sensorsTune,
		IntVectorTune* upSocketsTune,
		IntVectorTune* downSocketsTune,
		intTune* timeProfileTune,
		PeriodValuesCollection* dpvcollection);
	
	~SensorsSocketsControl();
	
	virtual void ExecuteStep();
	virtual void FillScreen(uint8_t snum);

	
	virtual uint16_t _get_low_aim_val();
	virtual uint16_t _get_high_aim_val();
	
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
	uint16_t low_aim_val = 0;
	uint16_t high_aim_val = 0;
	
};

class MixControl : public SocketsControl
{
public:
	MixControl(uint16_t id,
		const char* name,
		const char* uid,
		intTune* onOffTune,
		IntVectorTune* SocketsTune,
		intTune* modeTune,
		intTune* periodOnTune,
		intTune* periodOffTune,
		PeriodValuesCollection* dpvcollection);
		
	virtual void ExecuteStep();
	virtual void FillScreen(uint8_t snum);

protected:
	intTune* ModeTune;
	intTune* PeriodOnTune;
	intTune* PeriodOffTune;
	PeriodValuesCollection* DPVCollection;
	time_t swichedSeconds = 0;
};

#endif	
