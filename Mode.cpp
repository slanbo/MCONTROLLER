#include "Mode.hpp"
#include "ControlObjectsExt.hpp"
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
	if (isOn())
	{
		const char blank[2] = { ' ', 0 };
		
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
		Info_FirstString->SetIntText(controlsVector.at(currentControlIndex)->_get_current_val(), 5);
		Info_FirstString->SetChars(blank, false);	
		Info_FirstString->SetChars(controlsVector.at(currentControlIndex)->GetSensorsUnit(), false);
		Info_FirstString->FillEndBySpaces();
		Info_FirstString->_setUpdated(true);

		char isecond[] = "Цель:\0";
		Info_SecondString->SetChars(isecond, true);
		Info_SecondString->SetIntText(controlsVector.at(currentControlIndex)->_get_aim_val(), 5);
		Info_SecondString->SetChars(blank, false);
		Info_SecondString->SetChars(controlsVector.at(currentControlIndex)->GetSensorsUnit(), false);
		Info_SecondString->FillEndBySpaces();
		Info_SecondString->_setUpdated(true);
	
		char ithird[] = "Нагр.:\0";
		Info_ThirdString->SetChars(ithird, true);
		Info_ThirdString->SetIntText(controlsVector.at(currentControlIndex)->GetSocketsPowerVT(), 5);
		Info_ThirdString->SetChars(blank, false);
		char vt[] = "ВТ\0";
		Info_ThirdString->SetChars(vt, true);
		Info_ThirdString->FillEndBySpaces();
		Info_ThirdString->_setUpdated(true);
	
		char ifourth[] = "_____________\0";
		Info_FourthString->SetChars(ifourth, true);
		Info_FourthString->FillEndBySpaces();
		Info_FourthString->_setUpdated(true);
	
		currentControlIndex++;
		if (currentControlIndex == controlsVector.size())
		{
			currentControlIndex = 0;
			allscreensfilled = true;
		}
	}
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
	std::string name)
	: ControlsMode(ID, name)
{
	DatePeriodValuesCollection* airTempDVPC = new DatePeriodValuesCollection();
	airTempDVPC->addPeriodTune(3, 0, 1, 23, 59, 0, 0, 0, 0, 0, &airFixTemp);
	
	airTempControl = new (first_SensorsSocketsControl)SensorsSocketsControl
		(
		"Темпер. возд:", 
		&airTempControlOnOffTune,
		&airTempControlSwichOnIfMotionPeriod,
		&airTempControlSensors,
		&airTempControlUpSockets,
		&airTempControlDownSockets,
		&airTempControlTimeProfile,
		airTempDVPC);
	
	
	DatePeriodValuesCollection* batTempDVPC = new DatePeriodValuesCollection();
	batTempDVPC->addPeriodTune(0, 0, 1, 6, 59, 0, 0, 0, 0, 0, &batNightFixTemp);
	batTempDVPC->addPeriodTune(0, 7, 0, 22, 59, 0, 0, 0, 0, 0, &batDayFixTemp);
	batTempDVPC->addPeriodTune(0, 23, 0, 23, 59, 0, 0, 0, 0, 0, &batNightFixTemp);
	
	
	batTempControl = new (second_SensorsSocketsControl)SensorsSocketsControl
			(
		"Темпер. бат:", 
		&batTempControlOnOffTune,
		nullptr,
		&batTempControlSensors,
		&batTempControlUpSockets,
		&batTempControlDownSockets,
		&batTempControlTimeProfile,
		batTempDVPC);
	
	DatePeriodValuesCollection* CODVPC = new DatePeriodValuesCollection();
	CODVPC->addPeriodTune(0, 0, 1, 23, 59, 0, 0, 0, 0, 0, &CODangerLevel);

	coControl = new (third_SensorsSocketsControl)SensorsSocketsControl
		(
		"Газ:", 
		&coControlOnOffTune,
		&COControlSwichOnIfMotionPeriod,
		&COControlSensors,
		&COControlUpSockets,
		&COControlDownSockets,
		&COControlTimeProfile,
		CODVPC);	
	
	DatePeriodValuesCollection* lightDVPC = new DatePeriodValuesCollection();
	lightDVPC->addPeriodTune(0, 0, 1, 23, 59, 0, 0, 0, 0, 0, &LightEdge);
	
	lightControl = new(forth_SensorsSocketsControl)SensorsSocketsControl
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
	
}




