#ifndef __CONTROLOBJECTS__H
#define __CONTROLOBJECTS__H

#include "Control.hpp"
#include "MixControl.hpp"
#include "DateControl.hpp"
#include "MotionControl.hpp"

void InitControls();

extern SensorsSocketsControl airTempContr;
extern SensorsSocketsControl batTempContr;
extern SensorsSocketsControl coContr;
extern SensorsSocketsControl lightControl;
extern SensorsSocketsControl mashingControl;
extern SensorsSocketsControl boilingControl;
extern MixControl pumpControl;

extern DateControl delayBeginControl;
extern DateControl delayEndControl;
extern MotionControl motionControl;

extern SensorsSocketsControl dryingTempContr;
extern SensorsSocketsControl dryingHumidityContr;
extern MixControl dryingVentControl;

void ControlObjectsInit();



#endif	