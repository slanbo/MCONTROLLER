#ifndef __MODES__H
#define __MODES__H

#include "main.h"
#include "Mode.hpp"

extern ControlsMode HabitatMode;
extern ControlsMode BeerMashingMode;
extern ControlsMode BeerBoilingMode;
extern ControlsMode DryingMode;
extern std::vector<ModeBase *> Modes;
void ModeObjectsInit();

#endif	