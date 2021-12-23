#include "Mode.hpp"
#include "Control.hpp"
#include "TuneObjectsExt.hpp"
#include <vector>

Habitat* HabitatMode =  new Habitat(0, "Контроль среды");
BeerPreparing* BeerPreparingMode = new BeerPreparing(1, "Пригот-ние пива"); 
Drying* DryingMode = new Drying(2, "Сушка"); 

std::vector<ControlsMode*> Modes = { HabitatMode, BeerPreparingMode, DryingMode };

void ModeObjectsInit()
{
	HabitatMode->init();
	BeerPreparingMode->init();
}
