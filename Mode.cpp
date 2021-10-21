#include "Mode.hpp"
#include "ScreenObjectsExt.hpp"

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
	airTempControl = new TempControl()
	
}
