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
ControlsMode::ControlsMode(uint16_t ID, std::string name)
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
	std::string name)
	: ControlsMode(ID, name)
{
	
	
}

void Habitat::FillScreen()
{
	/*currentControlIndex++;
	if (currentControlIndex == controlsVector.size())
		currentControlIndex = 0;
		
	controlsVector.at(currentControlIndex)->FillScreen();*/
	Info_Header.SetText(Name, true);
	airTempControl->FillScreen();
	
}


void Habitat::ExecuteStep()
{
	airTempControl->ExecuteStep();
}


bool Habitat::isActive()
{
	return true;
}


void ControlsMode::init()
{
}


void Habitat::init()
{
	DatePeriodValuesCollection* dpvc = new DatePeriodValuesCollection();
	airFixTemp._setVal(23);
	dpvc->addPeriodTune(0, 0, 1, 23, 59, 0, 0, 0, 0, 0, &airFixTemp);
	
	airTempControl = new SensorsSocketsControl
		(
		"air control", 
		&airTempControlOnOffTune,
		&airTempControlSensors,
		&airTempControlUpSockets,
		&airTempControlDownSockets,
		&airTempControlTimeProfile,
		dpvc);
	
	
	/*batTempControl = new SensorsSocketsControl
		(
		"bat control", 
		&batTempControlOnOffTune,
		&batTempControlSensors,
		&batTempControlUpSockets,
		&batTempControlDownSockets,
		&batTempControlTimeProfile,
		createBatTempTimeProfile);
	
	coControl = new SensorsSocketsControl
		(
		"CO control", 
		&coControlOnOffTune,
		&COControlSensors,
		&COControlUpSockets,
		&COControlDownSockets,
		&COControlTimeProfile,
		createCOTimeProfile);	
	
	lightControl = new SensorsSocketsControl
		(
		"Light control", 
		&lightControlOnOffTune,
		&lightControlSensors,
		&lightControlUpSockets,
		&lightControlDownSockets,
		&lightControlTimeProfile,
		createLightTimeProfile);	*/
	
}
