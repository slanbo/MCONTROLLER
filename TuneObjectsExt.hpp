#ifndef __TUNES__H
#define __TUNES__H

#include "Tune.hpp"
#include <vector>
	
#define FLASH_TUNES_QUANT 54

//extern intTune plugTune;
extern	intTune modeIndex;
extern	intTune airTempProfileIndex;
extern	intTune mashingProfileIndex;
extern	intTune boilingProfileIndex;
extern	intTune airFixTemp;
extern	intTune batFixTemp;
extern	intTune yearTune;
extern	intTune monthTune;
extern	intTune dateTune;
extern	intTune hourTune;
extern	intTune minuteTune;
extern	intTune weekDayTune;
extern intTune CODangerLevel;
extern intTune airTempControlOnOffTune;
extern intTune batTempControlOnOffTune;
extern intTune coControlOnOffTune;
extern intTune batTempProfileIndex;
extern intTune LightEdge;
extern intTune lightControlOnOffTune;
extern intTune LightProfileIndex;
	
extern intTune airTempShowControlInfo;
extern intTune batTempShowControlInfo;
extern intTune coShowControlInfo;
extern intTune lightShowControlInfo;

extern intTune upSocketLoadPower;
extern intTune downSocketLoadPower;
extern intTune v12LoadPower;
	
extern intTune dayPCounterFirstByte;
extern intTune dayPCounterSecondByte;

extern intTune nightPCounterFirstByte;
extern intTune nightPCounterSecondByte;
	
extern intTune PCounterBeginDate;
extern intTune PCounterBeginMonth;
extern intTune PCounterBeginYear;
extern intTune PCounterBeginHour;
extern intTune PCounterBeginMinute;
	
extern intTune LightSwitchOffDelay;
	
extern intTune beerModeIndex;
	
//beer mashing
extern intTune  mashingPause1Temp;
extern intTune  mashingPause1Time;

extern intTune  mashingPause2Temp;
extern intTune  mashingPause2Time;
	
extern intTune  mashingPause3Temp;
extern intTune  mashingPause3Time;

extern intTune  mashingPause4Temp;
extern intTune  mashingPause4Time;

extern intTune  mashingPause5Temp;
extern intTune  mashingPause5Time;

extern intTune  mashingPause6Temp;
extern intTune  mashingPause6Time;

//beer boiling

extern intTune  boilingPause1Temp;
extern intTune  boilingPause1Time;

extern intTune  boilingPause2Temp;
extern intTune  boilingPause2Time;
	
extern intTune  boilingPause3Temp;
extern intTune  boilingPause3Time;
	
extern intTune PumpMode;
extern intTune SwitchedOnPumpTime;
extern intTune SwitchedOffPumpTime;	
	
extern intTune dryingAirTempProfileIndex;
extern intTune DryingFixTemp;
extern intTune dryingAirDryProfileIndex;
extern intTune DryingDryLevel;	

extern intTune MashingOnOffTune;	
extern intTune BoilingOnOffTune;	
extern intTune PumpOnOffTune;	
	

extern intTune delayBeginOnOffTune;	
extern intTune delayEndOnOffTune;	

extern intTune dryingTempOnOffTune;	
extern intTune dryingTempProfileIndex;	

extern intTune dryingHumidityOnOffTune;	
extern intTune humiditiNullLevelTune;	

extern intTune MotionControlOnOffTune; 
extern intTune OnIfMotionPeriod;

extern intTune dryingFixTemp;

extern intTune dryingFixTempDay;
extern intTune dryingFixTempNight;

extern intTune dryingVentMode;

extern intTune dryingVentOnPeriod;	
extern intTune dryingVentOffPeriod;

extern intTune dryingVentOnOffTune;
extern intTune longPeriodMotionControlOnOffTune;
extern intTune longPeriodOnIfMotionPeriod;

extern std::vector <intTune*> flashTunesV;

extern intTune dayPCounterOnOffTune;
extern intTune nightPCounterOnOffTune;

extern IntVectorTune airTempControlSensors;
extern IntVectorTune airTempControlUpSockets;
extern IntVectorTune airTempControlDownSockets;
extern intTune airTempControlTimeProfile;


//bat Temp control sensors & sockets
extern IntVectorTune batTempControlSensors;
extern IntVectorTune batTempControlUpSockets;
extern IntVectorTune batTempControlDownSockets;
extern intTune batTempControlTimeProfile;


//light control sensors & sockets
extern IntVectorTune lightControlSensors;
extern IntVectorTune lightControlUpSockets;
extern IntVectorTune lightControlDownSockets;
extern intTune lightControlTimeProfile;

//co control sensors sockets
extern IntVectorTune COControlSensors;
extern IntVectorTune COControlUpSockets;
extern IntVectorTune COControlDownSockets;
extern intTune COControlTimeProfile;

//humodity control sensors sockets
extern IntVectorTune humidityControlSensors;
extern IntVectorTune humidityControlUpSockets;
extern IntVectorTune humidityControlDownSockets;
extern intTune humidityControlTimeProfile;

extern intTune delayBeginYear;
extern intTune delayBeginMonth;
extern intTune delayBeginDate;
extern intTune delayBeginHour;	
extern intTune delayBeginMinute;	

//end date
extern intTune delayEndYear;
extern intTune delayEndMonth;
extern intTune delayEndDate;
extern intTune delayEndHour;	
extern intTune delayEndMinute;	

extern FlashTune* lastFlashTune;

void writesTunesToFlash();
void readTunesFromFlash();
void clearTunesInFlash();
void setDefaultTuneVals();
	
#endif 