#include "Mode.hpp"
#include "ControlObjectsExt.hpp"
#include "Control.hpp"
#include "TuneObjectsExt.hpp"
#include <vector>




Habitat* HabitatMode =  new Habitat(0, "Контр. среды");
BeerPreparing* BeerPreparingMode = new BeerPreparing(1, "Пригот. пива"); 

std::vector<ControlsMode*> Modes = { HabitatMode, BeerPreparingMode };

void ModeObjectsInit()
{
		Modes.at(modeIndex._getVal())->init();
}
