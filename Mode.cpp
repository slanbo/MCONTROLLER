#include "Mode.hpp"
#include "Control.hpp"
#include "TuneObjectsExt.hpp"
#include "Auxiliary.hpp"

ModeBase::ModeBase(uint16_t ID, const char* name)
	: BaseObject(ID, name) 
{
}

bool ModeBase::isActive()
{
	return ModeTune->_getVal() == id;
}

//controls mode
ControlsMode::ControlsMode(uint16_t ID, const char* name)
	: ModeBase(ID, name)
{
	
}


bool ControlsMode::isActive()
{
	return true;
}


bool ControlsMode::isOn()
{
	if (modeIndex._getVal() == id)
		return true;
	else
		return false;
}

void ControlsMode::FillScreen()
{
		Info_Header->ClearText();
		Info_Header->SetChars(Name, false);
		Info_Header->FillEndBySpaces();
		Info_Header->_setUpdated(true);
}

void ControlsMode::ExecuteStep()
{
	if (isOn())
	{
	for(auto e : controlsVector)
		e->ExecuteStep();
	}
}

// habitat

Habitat::Habitat(uint16_t ID, 
	const char* name)
	: ControlsMode(ID, name)
{
	PeriodValuesCollection* airTempDVPC = new PeriodValuesCollection();
	DatePeriodValue *adpv = new DatePeriodValue(1, "All time", 3, 0, 1, 23, 59, 0, 0, 0, 0, 0, &airFixTemp);
	airTempDVPC->addPeriodValue((PeriodValue*)adpv);
	
	airTempControl = new SensorsSocketsControl
		(
		"Темпер. возд:", 
		&airTempControlOnOffTune,
		&airTempControlSwichOnIfMotionPeriod,
		&airTempControlSensors,
		&airTempControlUpSockets,
		&airTempControlDownSockets,
		&airTempControlTimeProfile,
		airTempDVPC);
	
	
	PeriodValuesCollection* batTempDVPC = new PeriodValuesCollection();
	DatePeriodValue *bdpv1 = new DatePeriodValue(1, "Night time 1", 0, 0, 1, 6, 59, 0, 0, 0, 0, 0, &batNightFixTemp);
	batTempDVPC->addPeriodValue((PeriodValue*)bdpv1);
	DatePeriodValue *bdpv2 = new DatePeriodValue(2, "Day time", 0, 7, 0, 22, 59, 0, 0, 0, 0, 0, &batDayFixTemp);
	batTempDVPC->addPeriodValue((PeriodValue*)bdpv2);
	DatePeriodValue *bdpv3 = new DatePeriodValue(3, "Night time 2", 0, 23, 0, 23, 59, 0, 0, 0, 0, 0, &batNightFixTemp);
	batTempDVPC->addPeriodValue((PeriodValue*)bdpv3);
	
	
	batTempControl = new SensorsSocketsControl
			(
		"Темпер. бат:", 
		&batTempControlOnOffTune,
		nullptr,
		&batTempControlSensors,
		&batTempControlUpSockets,
		&batTempControlDownSockets,
		&batTempControlTimeProfile,
		batTempDVPC);
	
	PeriodValuesCollection* CODVPC = new PeriodValuesCollection();
	DatePeriodValue *cdpv = new DatePeriodValue(1, "All day", 0, 0, 1, 23, 59, 0, 0, 0, 0, 0, &CODangerLevel);
	CODVPC->addPeriodValue((PeriodValue*)cdpv);

	coControl = new SensorsSocketsControl
		(
		"Газ:", 
		&coControlOnOffTune,
		&COControlSwichOnIfMotionPeriod,
		&COControlSensors,
		&COControlUpSockets,
		&COControlDownSockets,
		&COControlTimeProfile,
		CODVPC);	
	
	PeriodValuesCollection* lightDVPC = new PeriodValuesCollection();
	DatePeriodValue *ldpv = new DatePeriodValue(1, "All day", 0, 0, 1, 23, 59, 0, 0, 0, 0, 0, &LightEdge);
	lightDVPC->addPeriodValue((PeriodValue*)ldpv);
	
	lightControl = new SensorsSocketsControl
		(
		"Освещение:", 
		&lightControlOnOffTune,
		&lightControlSwichOnIfMotionPeriod,
		&lightControlSensors,
		&lightControlUpSockets,
		&lightControlDownSockets,
		&lightControlTimeProfile,
		lightDVPC);
	
	controlsVector.push_back(airTempControl);
	controlsVector.push_back(batTempControl);
	controlsVector.push_back(coControl);
	controlsVector.push_back(lightControl);
}

Habitat::~Habitat()
{
	delete airTempControl;
	delete coControl;
	delete lightControl;
}


void ControlsMode::init()
{
	
}

void Habitat::init()
{
	for (auto elem : controlsVector)
	{
		SensorsSocketsControl* control = (SensorsSocketsControl*)elem;
		control->init();
	}
}

BeerPreparing::BeerPreparing(uint16_t ID, 
	const char* name)
	: ControlsMode(ID, name)
{
	mashingDVPC->addPeriodValue((PeriodValue*)mtp_1);
	mashingDVPC->addPeriodValue((PeriodValue*)mtp_2);
	mashingDVPC->addPeriodValue((PeriodValue*)mtp_3);
	mashingDVPC->addPeriodValue((PeriodValue*)mtp_4);
	mashingDVPC->addPeriodValue((PeriodValue*)mtp_5);
	mashingDVPC->addPeriodValue((PeriodValue*)mtp_6);
	
	mashingControl = new SensorsSocketsControl
		(
		"Темпер. паузы:", 
		&MashingOnOffTune,
		nullptr,
		&boilingMashingControlSensors,
		&boilingMashingControlUpSockets,
		&boilingMashingControlDownSockets,
		nullptr,
		mashingDVPC);
	
	boilingTempDVPC->addPeriodValue((PeriodValue*)btp_1);
	boilingTempDVPC->addPeriodValue((PeriodValue*)btp_2);
	boilingTempDVPC->addPeriodValue((PeriodValue*)btp_3);

	
	
	boilingControl = new SensorsSocketsControl
			(
		"Варка:", 
		&batTempControlOnOffTune,
		nullptr,
		&boilingMashingControlSensors,
		&boilingMashingControlUpSockets,
		&boilingMashingControlDownSockets,
		nullptr,
		boilingTempDVPC);
	
	
	pumpControl = new PumpControl(1,
		"Насос",
		&PumpOnOffTune,
		&pumpControlSockets,
		&PumpMode,
		&SwitchedOnPumpTime,
		&SwitchedOffPumpTime,
		mashingDVPC,
		boilingTempDVPC);
	
	controlsVector.push_back(mashingControl);
	controlsVector.push_back(boilingControl);
	controlsVector.push_back(pumpControl);
	
}


void BeerPreparing::init()
{
	for (auto elem : controlsVector)
	{
		SensorsSocketsControl* control = (SensorsSocketsControl*)elem;
		control->init();
	}
}

void BeerPreparing::ExecuteStep()
{
	if (isOn())
	{
		controlsVector.at(beerModeIndex._getVal())->ExecuteStep();
		controlsVector.at(2)->ExecuteStep();
	}
}


Drying::Drying(uint16_t ID, 
	const char* name)
	: ControlsMode(ID, name)
{
}


void Drying::init()
{
}


GreenHouse::GreenHouse(uint16_t ID, 
	const char* name)
	: ControlsMode(ID, name)
{
}


void GreenHouse::init()
{
}
