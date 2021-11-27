#include "Mode.hpp"
#include "portable.h"

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
		Info_Header->SetText(Name, false);
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
	Info_Header->SetText(Name, true);
	//controlsVector.at(currentControlIndex)->FillScreen();
	Info_SubHeader->SetText(controlsVector.at(currentControlIndex)->Name, true);
	Info_FirstString->SetText("Текущ.: ", true);
	Info_FirstString->AddIntStr(controlsVector.at(currentControlIndex)->_get_current_val(), 5);
	Info_SecondString->SetText("Целев.: ", true);
	Info_SecondString->AddIntStr(controlsVector.at(currentControlIndex)->_get_aim_val(), 5);
	Info_ThirdString->SetText("Нагр.: ", true);
	Info_FourthString->SetText("______________", false);
	
	
	currentControlIndex++;
	
	if (currentControlIndex == controlsVector.size())
		currentControlIndex = 0;
}

void Habitat::ExecuteStep()
{
	airTempControl->ExecuteStep();
	coControl->ExecuteStep();
	lightControl->ExecuteStep();
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
	
	DatePeriodValuesCollection* dpvc = (DatePeriodValuesCollection*) pvPortMalloc(sizeof(DatePeriodValuesCollection));
	airFixTemp._setVal(23);
	dpvc->addPeriodTune(0, 0, 1, 23, 59, 0, 0, 0, 0, 0, &airFixTemp);
	
	void* atcptr = pvPortMalloc(sizeof(SensorsSocketsControl));
	
	airTempControl = new (atcptr) SensorsSocketsControl
		(
		"air control", 
		&airTempControlOnOffTune,
		&airTempControlSensors,
		&airTempControlUpSockets,
		&airTempControlDownSockets,
		&airTempControlTimeProfile,
		dpvc);
	
	coControl = new SensorsSocketsControl
		(
		"CO control", 
		&coControlOnOffTune,
		&COControlSensors,
		&COControlUpSockets,
		&COControlDownSockets,
		&COControlTimeProfile,
		dpvc);	
	
	
	lightControl = new SensorsSocketsControl
		(
		"Light control", 
		&lightControlOnOffTune,
		&lightControlSensors,
		&lightControlUpSockets,
		&lightControlDownSockets,
		&lightControlTimeProfile,
		dpvc);
	
	/*batTempControl = new SensorsSocketsControl
		(
		"bat control", 
		&batTempControlOnOffTune,
		&batTempControlSensors,
		&batTempControlUpSockets,
		&batTempControlDownSockets,
		&batTempControlTimeProfile,
		createBatTempTimeProfile);*/
	
	controlsVector.push_back(airTempControl);
	controlsVector.push_back(coControl);
	controlsVector.push_back(lightControl);
	
}
