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
	//Info_SubHeader.SetText(Name, false);
	//Info_FirstString.Set_Prefix_IntVal_Postfix_Text("Текущ.: ", airTempControl->_get_current_val(), 3, CO, true);
	//Info_SecondString.Set_Prefix_IntVal_Postfix_Text("Целев.: ", airTempControl->_get_aim_val(), 3, CO, true);
	//Info_ThirdString.Set_Prefix_IntVal_Postfix_Text("Нагр.(ВТ): ", 10, 4, "", true);
	//Info_FourthString.SetText("****************", false);
	
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
	
	DatePeriodValuesCollection* dpvc = (DatePeriodValuesCollection*) pvPortMalloc(sizeof(DatePeriodValuesCollection));
	airFixTemp._setVal(23);
	dpvc->addPeriodTune(0, 0, 1, 23, 59, 0, 0, 0, 0, 0, &airFixTemp);
	
	void* atcptr = pvPortMalloc(sizeof(SensorsSocketsControl));
	//SensorsSocketsControl* airTempControl = (SensorsSocketsControl*)ptr;
	
	
	airTempControl = new (atcptr) SensorsSocketsControl
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
