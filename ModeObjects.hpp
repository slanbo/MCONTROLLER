#include "Mode.hpp"
#include "ControlObjectsExt.hpp"
#include "Control.hpp"
#include "TuneObjectsExt.hpp"
#include <vector>




Habitat* HabitatMode =  new Habitat(0, "Контроль среды");
BeerPreparing* BeerPreparingMode = new BeerPreparing(1, "Пригот-ние пива"); 

std::vector<ControlsMode*> Modes = { HabitatMode, BeerPreparingMode };

void ModeObjectsInit()
{
	HabitatMode->init();
	BeerPreparingMode->init();
}
