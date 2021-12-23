#ifndef __MODEOBJECTS__H
#define __MODEOBJECTS__H

#include "main.h"
#include "Mode.hpp"


extern Habitat* HabitatMode;
extern BeerPreparing* BeerPreparingMode;
extern Drying* DryingMode;

extern std::vector<ControlsMode*> Modes;

void ModeObjectsInit();


#endif	