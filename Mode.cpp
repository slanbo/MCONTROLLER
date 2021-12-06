#include "Mode.hpp"
//#include "portable.h"

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
	DatePeriodValuesCollection* airTempDVPC = new DatePeriodValuesCollection();
	airTempDVPC->addPeriodTune(0, 0, 1, 23, 59, 0, 0, 0, 0, 0, &airFixTemp);
	
	airTempControl = new SensorsSocketsControl
		(
		"Темпер. возд:", 
		&airTempControlOnOffTune,
		&airTempControlSensors,
		&airTempControlUpSockets,
		&airTempControlDownSockets,
		&airTempControlTimeProfile,
		airTempDVPC);
	
	DatePeriodValuesCollection* batTempDVPC = new DatePeriodValuesCollection();
	batTempDVPC->addPeriodTune(0, 0, 1, 23, 59, 0, 0, 0, 0, 0, &batFixTemp);
	
	batTempControl = new SensorsSocketsControl
			(
		"Темпер. бат:", 
		&batTempControlOnOffTune,
		&batTempControlSensors,
		&batTempControlUpSockets,
		&batTempControlDownSockets,
		&batTempControlTimeProfile,
		batTempDVPC);
	
	DatePeriodValuesCollection* CODVPC = new DatePeriodValuesCollection();
	CODVPC->addPeriodTune(0, 0, 1, 23, 59, 0, 0, 0, 0, 0, &batFixTemp);
	
	coControl = new SensorsSocketsControl
		(
		"Газ:", 
		&coControlOnOffTune,
		&COControlSensors,
		&COControlUpSockets,
		&COControlDownSockets,
		&COControlTimeProfile,
		CODVPC);	
	
	DatePeriodValuesCollection* lightDVPC = new DatePeriodValuesCollection();
	lightDVPC->addPeriodTune(0, 0, 1, 23, 59, 0, 0, 0, 0, 0, &CODangerLevel);
	
	lightControl = new SensorsSocketsControl
		(
		"Освещение:", 
		&lightControlOnOffTune,
		&lightControlSensors,
		&lightControlUpSockets,
		&lightControlDownSockets,
		&lightControlTimeProfile,
		lightDVPC);
	
	controlsVector.push_back(airTempControl);
	controlsVector.push_back(coControl);
	controlsVector.push_back(lightControl);
}

Habitat::~Habitat()
{
	delete airTempControl;
	delete coControl;
	delete lightControl;
}

void Habitat::FillScreen()
{
	
	const char blank[2] = { ' ', 0};
		
	Info_Header->ClearText();
	Info_SubHeader->ClearText();
	Info_FirstString->ClearText();
	Info_SecondString->ClearText();
	Info_ThirdString->ClearText();
	Info_FourthString->ClearText();
	
	Info_Header->SetChars(Name, false);
	Info_Header->FillEndBySpaces();
	Info_Header->_setUpdated(true);
	
	Info_SubHeader->SetChars(controlsVector.at(currentControlIndex)->Name, false);
	Info_SubHeader->FillEndBySpaces();
	Info_SubHeader->_setUpdated(true);
	
	char ifirst[] = "Тек.:\0";
	Info_FirstString->SetChars(ifirst, true);
	//Info_FirstString->SetText("Тек.:", true);
	Info_FirstString->SetIntText(controlsVector.at(currentControlIndex)->_get_current_val(), 5);
	Info_FirstString->SetChars(blank, false);	
	Info_FirstString->SetChars(controlsVector.at(currentControlIndex)->GetSensorsUnit(), false);
	Info_FirstString->FillEndBySpaces();
	Info_FirstString->_setUpdated(true);

	char isecond[] = "Цель:\0";
	Info_SecondString->SetChars(isecond, true);
	//Info_SecondString->SetText("Цель:", true);
	Info_SecondString->SetIntText(controlsVector.at(currentControlIndex)->_get_aim_val(), 5);
	Info_SecondString->SetChars(blank, false);
	Info_SecondString->SetChars(controlsVector.at(currentControlIndex)->GetSensorsUnit(), false);
	Info_SecondString->FillEndBySpaces();
	Info_SecondString->_setUpdated(true);
	
	char ithird[] = "Нагр.:\0";
	Info_ThirdString->SetChars(ithird, true);
	//Info_ThirdString->SetText("Нагр.:", true);
	Info_ThirdString->FillEndBySpaces();
	Info_ThirdString->_setUpdated(true);
	
	char ifourth[] = "______________\0";
	Info_FourthString->SetChars(ifourth, true);
	//Info_FourthString->SetText("______________", false);
	Info_FourthString->FillEndBySpaces();
	Info_FourthString->_setUpdated(true);
	
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
	
	
	
}
