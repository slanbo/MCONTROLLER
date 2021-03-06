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
extern	intTune batNightFixTemp;
extern	intTune batDayFixTemp;
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
extern intTune midSocketLoadPower;
extern intTune downSocketLoadPower;
extern intTune v12LoadPower;
	
extern IntVectorTune dayPCounterVal;
extern IntVectorTune nightPCounterVal;
	
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
extern intTune  mashingPause1Active;
extern intTune  mashingPause1StayOn;


extern intTune  mashingPause2Temp;
extern intTune  mashingPause2Time;
extern intTune  mashingPause2Active;
extern intTune  mashingPause2StayOn;

	
extern intTune  mashingPause3Temp;
extern intTune  mashingPause3Time;
extern intTune  mashingPause3Active;
extern intTune  mashingPause3StayOn;



extern intTune  mashingPause4Temp;
extern intTune  mashingPause4Time;
extern intTune  mashingPause4Active;
extern intTune  mashingPause4StayOn;


extern intTune  mashingPause5Temp;
extern intTune  mashingPause5Time;
extern intTune  mashingPause5Active;
extern intTune  mashingPause5StayOn;

extern intTune  mashingPause6Temp;
extern intTune  mashingPause6Time;
extern intTune  mashingPause6Active;
extern intTune  mashingPause6StayOn;

//beer boiling

extern intTune  boilingPause1Temp;
extern intTune  boilingPause1Time;
extern intTune  boilingPause1Active;
extern intTune  boilingPause1StayOn;

extern intTune  boilingPause2Temp;
extern intTune  boilingPause2Time;
extern intTune  boilingPause2Active;
extern intTune  boilingPause2StayOn;
	
extern intTune  boilingPause3Temp;
extern intTune  boilingPause3Time;
extern intTune  boilingPause3Active;
extern intTune  boilingPause3StayOn;
	
extern IntVectorTune boilingMashingControlSensors;
extern IntVectorTune boilingMashingControlUpSockets;
extern IntVectorTune  boilingMashingControlDownSockets;


extern intTune PumpMode;
extern intTune SwitchedOnPumpTime;
extern intTune SwitchedOffPumpTime;	
	
extern intTune mashboilStayOnDelta;
extern intTune dryingAirTempProfileIndex;
extern intTune DryingFixTemp;
extern intTune dryingAirDryProfileIndex;
extern intTune DryingDryLevel;	
extern intTune MashingOnOffTune;	
extern intTune BoilingOnOffTune;	
extern intTune PumpOnOffTune;
extern IntVectorTune pumpControlSockets;	
extern intTune delayBeginOnOffTune;	
extern intTune delayEndOnOffTune;	
extern intTune humiditiNullLevelTune;	
extern intTune MotionControlOnOffTune; 
extern intTune OnIfMotionPeriod;
extern intTune longPeriodMotionControlOnOffTune;
extern intTune longPeriodOnIfMotionPeriod;
extern std::vector <intTune*> flashTunesV;
extern intTune dayPCounterOnOffTune;
extern intTune nightPCounterOnOffTune;
extern IntVectorTune airTempControlSensors;
extern IntVectorTune airTempControlUpSockets;
extern IntVectorTune airTempControlDownSockets;
extern intTune airTempControlTimeProfile;
extern intTune airTempControlSwichOnIfMotionPeriod;

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
extern intTune lightControlSwichOnIfMotionPeriod;

//co control sensors sockets
extern IntVectorTune COControlSensors;
extern IntVectorTune COControlUpSockets;
extern IntVectorTune COControlDownSockets;
extern intTune COControlTimeProfile;
extern intTune COControlSwichOnIfMotionPeriod;

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
extern IntVectorTune PCounterSockets;

extern intTune  dryingPause1Temp;
extern intTune  dryingPause1Time;
extern intTune  dryingPause1Active;
extern intTune  dryingPause1StayOn;

extern intTune  dryingPause2Temp;
extern intTune  dryingPause2Time;
extern intTune  dryingPause2Active;
extern intTune  dryingPause2StayOn;
	
extern intTune  dryingPause3Temp;
extern intTune  dryingPause3Time;
extern intTune  dryingPause3Active;
extern intTune  dryingPause3StayOn;
	
extern IntVectorTune dryingControlSensors;
extern IntVectorTune dryingControlUpSockets;
extern IntVectorTune  dryingControlDownSockets;


extern intTune dryingVentMode;
extern intTune SwitchedOnVentTime;
extern intTune SwitchedOffVentTime;	
	
extern intTune dryingStayOnDelta;



extern FlashTune* lastFlashTune;

void writesTunesToFlash();
void readTunesFromFlash();
void clearTunesInFlash();
void setDefaultTuneVals();
	
extern std::vector<intTune*> mashingTemperatureTunesVector;
extern std::vector<intTune*> mashingTimeTunesVector;
extern std::vector<intTune*> mashingActivityTunesVector;
extern std::vector<intTune*> mashingStayOnTunesVector;

extern std::vector<intTune*> boilingTemperatureTunesVector;
extern std::vector<intTune*> boilingTimeTunesVector;
extern std::vector<intTune*> boilingActivityTunesVector;
extern std::vector<intTune*> boilingStayOnTunesVector;

extern std::vector<intTune*> dryingTemperatureTunesVector;
extern std::vector<intTune*> dryingTimeTunesVector;
extern std::vector<intTune*> dryingActivityTunesVector;
extern std::vector<intTune*> dryingStayOnTunesVector;

extern intTune dryingTempOnOffTune;	
extern intTune dryingVentOnOffTune;	

extern IntVectorTune dryingVentControlSockets;

#endif 