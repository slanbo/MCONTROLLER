#include "Mode.hpp"
#include "ControlObjectsExt.hpp"
#include "Control.hpp"
#include <vector>

/*

ControlsMode BeerMashingMode("Пиво: ПАУЗЫ", &modeIndex, MashingControls);

std::vector<ControlBase *> BoilingControls = { 
	&boilingControl,
	&dayPCounter,
	&nightPCounter
};
ControlsMode BeerBoilingMode("Пиво: ВАРКА", &modeIndex, BoilingControls);

std::vector<ControlBase *> DryingControls = { 
	&dryingTempContr,
	&dryingHumidityContr,
	&dryingVentControl
};
ControlsMode DryingMode("Сушка", &modeIndex, DryingControls);
*/

//ModeBase* CurrentMode = nullptr;
Habitat* HabitatMode = nullptr;

//Habitat* HabitatMode = new Habitat(1, "Контр. среды");
//std::vector<ModeBase *> Modes = { HabitatMode };

void ModeObjectsInit()
{
}
