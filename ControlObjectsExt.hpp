#ifndef __CONTROLS__H
#define __CONTROLS__H

#include "TempControl.hpp"
#include "COControl.hpp"
#include "LightControl.hpp"
#include "MashingControl.hpp"
#include "BoilingControl.hpp"
#include "MixControl.hpp"
#include "HumidityControl.hpp"

void InitControls();

extern TempControl airTempContr;
extern TempControl batTempContr;
extern COControl coContr;
extern LightControl lightControl;
extern MashingControl mashingControl;
extern BoilingControl boilingControl;
extern MixControl pumpControl;

extern DateControl delayBeginControl;
extern DateControl delayEndControl;
extern MotionControl motionControl;

extern TempControl dryingTempContr;
extern HumidityControl dryingHumidityContr;
extern MixControl dryingVentControl;

void ControlObjectsInit();



#endif	