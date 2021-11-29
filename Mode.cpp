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
	DatePeriodValuesCollection* dpvc = (DatePeriodValuesCollection*) pvPortMalloc(sizeof(DatePeriodValuesCollection));
	airFixTemp._setVal(23);
	dpvc->addPeriodTune(0, 0, 1, 23, 59, 0, 0, 0, 0, 0, &airFixTemp);
	
	void* atcptr = pvPortMalloc(sizeof(SensorsSocketsControl));
	
	airTempControl = new(atcptr) SensorsSocketsControl
		(
		"Температура:", 
		&airTempControlOnOffTune,
		&airTempControlSensors,
		&airTempControlUpSockets,
		&airTempControlDownSockets,
		&airTempControlTimeProfile,
		dpvc);
	
	void* ccptr = pvPortMalloc(sizeof(SensorsSocketsControl));

	
	coControl = new(ccptr)SensorsSocketsControl
		(
		"Газ:", 
		&coControlOnOffTune,
		&COControlSensors,
		&COControlUpSockets,
		&COControlDownSockets,
		&COControlTimeProfile,
		dpvc);	
	
	void* lcptr = pvPortMalloc(sizeof(SensorsSocketsControl));
	
	lightControl = new(lcptr)SensorsSocketsControl
		(
		"Освещение:", 
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

Habitat::~Habitat()
{
	vPortFree(airTempControl);
	vPortFree(coControl);
	vPortFree(lightControl);
}

void Habitat::FillScreen()
{
	char blank[2] = { ' ', 0};
	
	Info_Header->SetText(Name, false);
	//controlsVector.at(currentControlIndex)->FillScreen();
	Info_SubHeader->SetText(controlsVector.at(currentControlIndex)->Name, false);
	
	Info_FirstString->SetText("Тек.: ", true);
	Info_FirstString->AddIntStr(controlsVector.at(currentControlIndex)->_get_current_val(), 4);
	Info_FirstString->AddChars(blank);
	Info_FirstString->AddChars(controlsVector.at(currentControlIndex)->GetSensorsUnit());
		
	Info_SecondString->SetText("Цель: ", true);
	Info_SecondString->AddIntStr(controlsVector.at(currentControlIndex)->_get_aim_val(), 4);
	Info_SecondString->AddChars(controlsVector.at(currentControlIndex)->GetSensorsUnit());
	
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
		"Температура:", 
		&airTempControlOnOffTune,
		&airTempControlSensors,
		&airTempControlUpSockets,
		&airTempControlDownSockets,
		&airTempControlTimeProfile,
		dpvc);
	
	void* ccptr = pvPortMalloc(sizeof(SensorsSocketsControl));

	
	coControl = new (ccptr)SensorsSocketsControl
		(
		"Газ:", 
		&coControlOnOffTune,
		&COControlSensors,
		&COControlUpSockets,
		&COControlDownSockets,
		&COControlTimeProfile,
		dpvc);	
	
	void* lcptr = pvPortMalloc(sizeof(SensorsSocketsControl));
	
	lightControl = new(lcptr)SensorsSocketsControl
		(
		"Освещение:", 
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
