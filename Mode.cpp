#include "Mode.hpp"

ModeBase::ModeBase(uint16_t ID, std::string name)
	: BaseObject(ID, name) 
{
}

bool ModeBase::isActive()
{
	return ModeTune->_getVal() == Index;
}




//controls mode
ControlsMode::ControlsMode(uint16_t ID, std::string name, std::vector<ControlBase *> controls)
	: ModeBase(ID, name)
{
	
}

void ControlsMode::FillScreen()
{
	if (isActive())
	{
		Info_Header.SetText(Name, false);
		for (auto control : Controls)
			control->FillScreen();
	}
}

void ControlsMode::ExecuteStep()
{
	if (isActive())
		for (auto control : Controls)
			control->ExecuteStep();
}




// habitat

Habitat::Habitat(uint16_t ID, 
	std::string name,
	std::vector<ControlBase *> controls)
	: ControlsMode(ID, name, controls)
{
	airTempControl = new SensorsSocketsControl
		(
		"air control", 
		&airTempControlOnOffTune,
		&airTempControlSensors,
		&airTempControlUpSockets,
		&airTempControlDownSockets,
		&airTempControlTimeProfile,
		createAirTempTimeProfile);
	
}
