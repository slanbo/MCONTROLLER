#include "Mode.hpp"
#include "ControlObjectsExt.hpp"
#include "Control.hpp"
#include <vector>


/*std::vector<ControlBase *> HabitatControls = { 
	&airTempContr,
	&batTempContr,
	&coContr,
	&lightControl,
	&dayPCounter,
	&nightPCounter
};

ControlsMode HabitatMode("Контр. среды:", &modeIndex, HabitatControls);

std::vector<ControlBase *> MashingControls = { 
	&mashingControl,
	&pumpControl,
	&dayPCounter,
	&nightPCounter

};
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

std::vector<ModeBase *> Modes = { &HabitatMode, &BeerMashingMode, &BeerBoilingMode, &DryingMode};

void ModeObjectsInit()
{
	uint8_t counter = 0;
	for (auto mode : Modes)
	{
		mode->init(counter);
		counter++;
	}
}*/