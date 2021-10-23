#ifndef __CONTROLS__H
#define __CONTROLS__H


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