#include "Tune.hpp"
#include <vector>

#define MAX_CONTROL_CONNECTED_SOCKETS_SIZE 2
#define MAX_CONTROL_CONNECTED_SENSORS_SIZE 2


intTune modeIndex(nullptr);
intTune airTempProfileIndex(&modeIndex);

intTune mashingProfileIndex(&airTempProfileIndex);
intTune boilingProfileIndex(&mashingProfileIndex);
intTune airFixTemp(&boilingProfileIndex);

intTune CODangerLevel(&airFixTemp);
intTune batDayFixTemp(&CODangerLevel);
intTune batNightFixTemp(&batDayFixTemp);
intTune airTempControlOnOffTune(&batNightFixTemp);
intTune batTempControlOnOffTune(&airTempControlOnOffTune);
intTune coControlOnOffTune(&batTempControlOnOffTune);
intTune batTempProfileIndex(&coControlOnOffTune);
intTune LightEdge(&batTempProfileIndex);
intTune lightControlOnOffTune(&LightEdge);
intTune LightProfileIndex(&lightControlOnOffTune);
intTune upSocketLoadPower(&LightProfileIndex);
intTune downSocketLoadPower(&upSocketLoadPower);
intTune v12LoadPower(&downSocketLoadPower);

intTune dayPCounterFirstByte(&v12LoadPower);
intTune dayPCounterSecondByte(&dayPCounterFirstByte);

intTune nightPCounterFirstByte(&dayPCounterSecondByte);
intTune nightPCounterSecondByte(&nightPCounterFirstByte);

intTune PCounterBeginDate(&nightPCounterSecondByte);
intTune PCounterBeginMonth(&PCounterBeginDate);
intTune PCounterBeginYear(&PCounterBeginMonth);
intTune PCounterBeginHour(&PCounterBeginYear);
intTune PCounterBeginMinute(&PCounterBeginHour);
intTune LightSwitchOffDelay(&PCounterBeginMinute);
intTune beerModeIndex(&LightSwitchOffDelay);
	
//beer mashing
intTune  mashingPause1Temp(&beerModeIndex);
intTune  mashingPause1Time(&mashingPause1Temp);
intTune  mashingPause1Active(&mashingPause1Time);
intTune  mashingPause1StayOn(&mashingPause1Active);

intTune  mashingPause2Temp(&mashingPause1StayOn);
intTune  mashingPause2Time(&mashingPause2Temp);
intTune  mashingPause2Active(&mashingPause2Time);
intTune  mashingPause2StayOn(&mashingPause2Active);
	
intTune  mashingPause3Temp(&mashingPause2StayOn);
intTune  mashingPause3Time(&mashingPause3Temp);
intTune  mashingPause3Active(&mashingPause3Time);
intTune  mashingPause3StayOn(&mashingPause3Active);

intTune  mashingPause4Temp(&mashingPause3StayOn);
intTune  mashingPause4Time(&mashingPause4Temp);
intTune  mashingPause4Active(&mashingPause4Time);
intTune  mashingPause4StayOn(&mashingPause4Active);

intTune  mashingPause5Temp(&mashingPause4StayOn);
intTune  mashingPause5Time(&mashingPause5Temp);
intTune  mashingPause5Active(&mashingPause5Time);
intTune  mashingPause5StayOn(&mashingPause5Active);

intTune  mashingPause6Temp(&mashingPause5StayOn);
intTune  mashingPause6Time(&mashingPause6Temp);
intTune  mashingPause6Active(&mashingPause6Time);
intTune  mashingPause6StayOn(&mashingPause6Active);

//beer boiling
intTune  boilingPause1Temp(&mashingPause6Time);
intTune  boilingPause1Time(&boilingPause1Temp);
intTune  boilingPause1Active(&boilingPause1Time);
intTune  boilingPause1StayOn(&boilingPause1Active);


intTune  boilingPause2Temp(&boilingPause1StayOn);
intTune  boilingPause2Time(&boilingPause2Temp);
intTune  boilingPause2Active(&boilingPause2Time);
intTune  boilingPause2StayOn(&boilingPause2Active);
	
intTune  boilingPause3Temp(&boilingPause2StayOn);
intTune  boilingPause3Time(&boilingPause3Temp);
intTune  boilingPause3Active(&boilingPause3Time);
intTune  boilingPause3StayOn(&boilingPause3Active);

IntVectorTune boilingMashingControlSensors(&boilingPause3StayOn, MAX_CONTROL_CONNECTED_SENSORS_SIZE);
IntVectorTune boilingMashingControlUpSockets(&boilingMashingControlSensors, MAX_CONTROL_CONNECTED_SOCKETS_SIZE);
IntVectorTune  boilingMashingControlDownSockets(&boilingMashingControlUpSockets, MAX_CONTROL_CONNECTED_SOCKETS_SIZE);

//pump
intTune PumpMode(&boilingMashingControlDownSockets);
intTune SwitchedOnPumpTime(&PumpMode);
intTune SwitchedOffPumpTime(&SwitchedOnPumpTime);	

//drying
intTune dryingAirTempProfileIndex(&SwitchedOffPumpTime);
intTune DryingFixTemp(&dryingAirTempProfileIndex);
intTune dryingAirDryProfileIndex(&DryingFixTemp);
intTune DryingDryLevel(&dryingAirDryProfileIndex);	

//on off
intTune MashingOnOffTune(&DryingDryLevel);	
intTune BoilingOnOffTune(&MashingOnOffTune);	
intTune PumpOnOffTune(&BoilingOnOffTune);	

IntVectorTune pumpControlSockets(&PumpOnOffTune, MAX_CONTROL_CONNECTED_SOCKETS_SIZE);


intTune delayBeginOnOffTune(&pumpControlSockets);	
intTune delayEndOnOffTune(&delayBeginOnOffTune);	

//drying temp
intTune dryingTempOnOffTune(&delayEndOnOffTune);	
intTune dryingTempProfileIndex(&dryingTempOnOffTune);	
intTune OnIfMotionPeriod(&dryingTempProfileIndex);
intTune dryingFixTemp(&OnIfMotionPeriod);

intTune dryingFixTempDay(&dryingFixTemp);
intTune dryingFixTempNight(&dryingFixTempDay);

intTune dryingVentMode(&dryingFixTempNight);


//drying humidity
intTune dryingHumidityOnOffTune(&dryingVentMode);	
intTune humiditiNullLevelTune(&dryingHumidityOnOffTune);	

//drying vent
intTune dryingVentOnOffTune(&humiditiNullLevelTune);

intTune dryingVentOnPeriod(&dryingVentOnOffTune);	
intTune dryingVentOffPeriod(&dryingVentOnPeriod);

intTune MotionControlOnOffTune(&dryingVentOffPeriod);

intTune longPeriodMotionControlOnOffTune(&MotionControlOnOffTune);
intTune longPeriodOnIfMotionPeriod(&longPeriodMotionControlOnOffTune);

intTune dayPCounterOnOffTune(&longPeriodOnIfMotionPeriod);
intTune nightPCounterOnOffTune(&dayPCounterOnOffTune);

//air Temp control sensors & sockets

IntVectorTune airTempControlSensors(&nightPCounterOnOffTune, MAX_CONTROL_CONNECTED_SENSORS_SIZE);
IntVectorTune airTempControlUpSockets(&airTempControlSensors, MAX_CONTROL_CONNECTED_SOCKETS_SIZE);
IntVectorTune airTempControlDownSockets(&airTempControlUpSockets, MAX_CONTROL_CONNECTED_SOCKETS_SIZE);
intTune airTempControlTimeProfile(&airTempControlDownSockets);
intTune airTempControlSwichOnIfMotionPeriod(&airTempControlTimeProfile);


//bat Temp control sensors & sockets
IntVectorTune batTempControlSensors(&airTempControlSwichOnIfMotionPeriod, MAX_CONTROL_CONNECTED_SENSORS_SIZE);
IntVectorTune batTempControlUpSockets(&batTempControlSensors, MAX_CONTROL_CONNECTED_SOCKETS_SIZE);
IntVectorTune batTempControlDownSockets(&batTempControlUpSockets, MAX_CONTROL_CONNECTED_SOCKETS_SIZE);
intTune batTempControlTimeProfile(&batTempControlDownSockets);


//light control sensors & sockets
IntVectorTune lightControlSensors(&batTempControlTimeProfile, MAX_CONTROL_CONNECTED_SENSORS_SIZE);
IntVectorTune lightControlUpSockets(&lightControlSensors, MAX_CONTROL_CONNECTED_SOCKETS_SIZE);
IntVectorTune lightControlDownSockets(&lightControlUpSockets, MAX_CONTROL_CONNECTED_SOCKETS_SIZE);
intTune lightControlTimeProfile(&lightControlDownSockets);
intTune lightControlSwichOnIfMotionPeriod(&lightControlTimeProfile);

//co control sensors sockets
IntVectorTune COControlSensors(&lightControlSwichOnIfMotionPeriod, MAX_CONTROL_CONNECTED_SENSORS_SIZE);
IntVectorTune COControlUpSockets(&COControlSensors, MAX_CONTROL_CONNECTED_SOCKETS_SIZE);
IntVectorTune COControlDownSockets(&COControlUpSockets, MAX_CONTROL_CONNECTED_SOCKETS_SIZE);
intTune COControlTimeProfile(&COControlDownSockets);
intTune COControlSwichOnIfMotionPeriod(&COControlTimeProfile);


//humodity control sensors sockets
IntVectorTune humidityControlSensors(&COControlSwichOnIfMotionPeriod, MAX_CONTROL_CONNECTED_SENSORS_SIZE);
IntVectorTune humidityControlUpSockets(&humidityControlSensors, MAX_CONTROL_CONNECTED_SOCKETS_SIZE);
IntVectorTune humidityControlDownSockets(&humidityControlUpSockets, MAX_CONTROL_CONNECTED_SOCKETS_SIZE);
intTune humidityControlTimeProfile(&humidityControlDownSockets);

//begin date
intTune delayBeginYear(&humidityControlTimeProfile);
intTune delayBeginMonth(&delayBeginYear);
intTune delayBeginDate(&delayBeginMonth);
intTune delayBeginHour(&delayBeginDate);	
intTune delayBeginMinute(&delayBeginHour);	

//end date
intTune delayEndYear(&delayBeginMinute);
intTune delayEndMonth(&delayEndYear);
intTune delayEndDate(&delayEndMonth);
intTune delayEndHour(&delayEndDate);	
intTune delayEndMinute(&delayEndHour);	

intTune yearTune(&delayEndMinute);
intTune monthTune(&yearTune);
intTune dateTune(&monthTune);
intTune hourTune(&dateTune);
intTune minuteTune(&hourTune);
intTune weekDayTune(&minuteTune);

IntVectorTune IRMSensorsTune(&weekDayTune, MAX_CONTROL_CONNECTED_SENSORS_SIZE);

IntVectorTune PCounterSockets(&IRMSensorsTune, MAX_CONTROL_CONNECTED_SOCKETS_SIZE);

FlashTune* lastFlashTune = &PCounterSockets;

std::vector<intTune*> mashingTemperatureTunesVector = { &mashingPause1Temp, &mashingPause2Temp, &mashingPause3Temp, 
														&mashingPause4Temp, &mashingPause5Temp, &mashingPause6Temp};
std::vector<intTune*> mashingTimeTunesVector =		  {&mashingPause1Time, &mashingPause2Time, &mashingPause3Time,
													   &mashingPause4Time, &mashingPause5Time, &mashingPause6Time};
std::vector<intTune*> mashingActivityTunesVector = {&mashingPause1Active, &mashingPause2Active, &mashingPause3Active,
													&mashingPause4Active, &mashingPause5Active, &mashingPause6Active};

std::vector<intTune*> mashingStayOnTunesVector = {&mashingPause1StayOn, &mashingPause2StayOn,&mashingPause3StayOn,
													&mashingPause4StayOn,&mashingPause5StayOn,&mashingPause6StayOn};
	
std::vector<intTune*> boilingTemperatureTunesVector = {&boilingPause1Temp, &boilingPause2Temp, &boilingPause3Temp};
std::vector<intTune*> boilingTimeTunesVector = { &boilingPause1Time, &boilingPause2Time, &boilingPause3Time};
std::vector<intTune*> boilingActivityTunesVector = {&boilingPause1Active, &boilingPause2Active, &boilingPause3Active};
std::vector<intTune*> boilingStayOnTunesVector = { &boilingPause1StayOn, &boilingPause2StayOn, &boilingPause3StayOn };
