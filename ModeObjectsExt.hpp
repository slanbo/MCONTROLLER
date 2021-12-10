#ifndef __MODES__H
#define __MODES__H

#include "main.h"
#include "Mode.hpp"


extern Habitat* HabitatMode;
extern BeerPreparing* BeerPreparingMode;
extern std::vector<ControlsMode*> Modes;

void ModeObjectsInit();


#endif	