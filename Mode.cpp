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
	airTempControl = new SensorsSocketsControl
		(
		"Темпер. возд:", 
		"HAB_AIR_T",
		&airTempControlOnOffTune,
		&airTempControlSwichOnIfMotionPeriod,
		&airTempControlSensors,
		&airTempControlUpSockets,
		&airTempControlDownSockets,
		&airTempControlTimeProfile,
		airTempDVPC);
	
	batTempControl = new SensorsSocketsControl
			(
		"Темпер. бат:", 
		"HAB_BAT_T",
		&batTempControlOnOffTune,
		nullptr,
		&batTempControlSensors,
		&batTempControlUpSockets,
		&batTempControlDownSockets,
		&batTempControlTimeProfile,
		batTempDVPC);
	
	coControl = new SensorsSocketsControl
		(
		"Газ:", 
		"HAB_GAS",
		&coControlOnOffTune,
		&COControlSwichOnIfMotionPeriod,
		&COControlSensors,
		&COControlUpSockets,
		&COControlDownSockets,
		&COControlTimeProfile,
		CODVPC);	
	
	lightControl = new SensorsSocketsControl
		(
		"Освещение:", 
		"HAB_LIGHT",
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
	delete batTempControl;
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
	
	mashingControl = new SensorsSocketsControl
		(
		"Темпер. паузы:", 
		"BEER_MASH_PAUS",
		&MashingOnOffTune,
		nullptr,
		&boilingMashingControlSensors,
		&boilingMashingControlUpSockets,
		&boilingMashingControlDownSockets,
		nullptr,
		mashingDVPC);
	
	boilingControl = new SensorsSocketsControl
			(
		"Варка:", 
		"BEER_BOIL_PAUS",
		&batTempControlOnOffTune,
		nullptr,
		&boilingMashingControlSensors,
		&boilingMashingControlUpSockets,
		&boilingMashingControlDownSockets,
		nullptr,
		boilingTempDVPC);
	
	
	pumpControl = new MixControl(1,
		"Насос",
		"BEER_PUMP",
		&PumpOnOffTune,
		&pumpControlSockets,
		&PumpMode,
		&SwitchedOnPumpTime,
		&SwitchedOffPumpTime,
		mashingDVPC);
	
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
	airTempControl = new SensorsSocketsControl
			(
		"Контр. темпер.:", 
		"DRY_AIR_T",
		&dryingTempOnOffTune,
		nullptr,
		&dryingControlSensors,
		&dryingControlUpSockets,
		&dryingControlDownSockets,
		nullptr,
		dryingTempDVPC);
	
	ventControl = new MixControl(1,
		"Вентилятор",
		"DRY_VENT",
		&dryingVentOnOffTune,
		&dryingVentControlSockets,
		&dryingVentMode,
		&SwitchedOnVentTime,
		&SwitchedOffVentTime,
		dryingTempDVPC);
	
	controlsVector.push_back(airTempControl);
	controlsVector.push_back(ventControl);
	
}


void Drying::init()
{
	for (auto elem : controlsVector)
	{
		SensorsSocketsControl* control = (SensorsSocketsControl*)elem;
		control->init();
	}
}


GreenHouse::GreenHouse(uint16_t ID, 
	const char* name)
	: ControlsMode(ID, name)
{
}


void GreenHouse::init()
{
}
