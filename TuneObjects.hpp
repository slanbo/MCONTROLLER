#include "Tune.hpp"
#include "TuneObjectsExt.hpp"
#include <vector>

#define MAX_CONTROL_CONNECTED_SOCKETS_SIZE 2
#define MAX_CONTROL_CONNECTED_SENSORS_SIZE 2


intTune modeIndex(nullptr);
intTune airTempProfileIndex(&modeIndex);

intTune mashingProfileIndex(&airTempProfileIndex);
intTune boilingProfileIndex(&mashingProfileIndex);
intTune airFixTemp(&boilingProfileIndex);

DateTune yearTune(DateTimeParts::YEAR);
DateTune monthTune(DateTimeParts::MONTH);
DateTune dateTune(DateTimeParts::DATE);
DateTune hourTune(DateTimeParts::HOUR);
DateTune minuteTune(DateTimeParts::MINUTE);
DateTune weekDayTune(DateTimeParts::WEEKDAY);
intTune CONullLevel(&airFixTemp);
intTune batFixTemp(&CONullLevel);
intTune airTempControlOnOffTune(&batFixTemp);
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

intTune  mashingPause2Temp(&mashingPause1Time);
intTune  mashingPause2Time(&mashingPause2Temp);
	
intTune  mashingPause3Temp(&mashingPause2Time);
intTune  mashingPause3Time(&mashingPause3Temp);

intTune  mashingPause4Temp(&mashingPause3Time);
intTune  mashingPause4Time(&mashingPause4Temp);

intTune  mashingPause5Temp(&mashingPause4Time);
intTune  mashingPause5Time(&mashingPause5Temp);

intTune  mashingPause6Temp(&mashingPause5Time);
intTune  mashingPause6Time(&mashingPause6Temp);

//beer boiling
intTune  boilingPause1Temp(&mashingPause6Time);
intTune  boilingPause1Time(&boilingPause1Temp);

intTune  boilingPause2Temp(&boilingPause1Time);
intTune  boilingPause2Time(&boilingPause2Temp);
	
intTune  boilingPause3Temp(&boilingPause2Time);
intTune  boilingPause3Time(&boilingPause3Temp);

//pump
intTune PumpMode(&boilingPause3Time);
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



intTune delayBeginOnOffTune(&PumpOnOffTune);	
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
IntVectorTune airTempControlSockets(&airTempControlSensors, MAX_CONTROL_CONNECTED_SOCKETS_SIZE);

//bat Temp control sensors & sockets
IntVectorTune batTempControlSensors(&airTempControlSockets, MAX_CONTROL_CONNECTED_SENSORS_SIZE);
IntVectorTune batTempControlSockets(&batTempControlSensors, MAX_CONTROL_CONNECTED_SOCKETS_SIZE);

//light control sensors & sockets
IntVectorTune lightControlSensors(&batTempControlSockets, MAX_CONTROL_CONNECTED_SENSORS_SIZE);
IntVectorTune lightControlSockets(&lightControlSensors, MAX_CONTROL_CONNECTED_SOCKETS_SIZE);

//co control sensors sockets
IntVectorTune COControlSensors(&lightControlSockets, MAX_CONTROL_CONNECTED_SENSORS_SIZE);
IntVectorTune COControlSockets(&COControlSensors, MAX_CONTROL_CONNECTED_SOCKETS_SIZE);

//humodity control sensors sockets
IntVectorTune humidityControlSensors(&COControlSockets, MAX_CONTROL_CONNECTED_SENSORS_SIZE);
IntVectorTune humidityControlSockets(&humidityControlSensors, MAX_CONTROL_CONNECTED_SOCKETS_SIZE);

//begin date
intTune delayBeginYear(&humidityControlSockets);
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

FlashTune* lastFlashTune = &delayEndMinute;