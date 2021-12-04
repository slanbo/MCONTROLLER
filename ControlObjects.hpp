#include "TuneObjectsExt.hpp"
#include "DateControl.hpp"
#include "MotionControl.hpp"
#include "MixControl.hpp"
#include "TimeProfiles.hpp"
#include <vector>
#include "Control.hpp"
#include "PCounterControl.hpp"





/*DateControl delayBeginControl(
	"Отлож. старт:",
	&delayBeginOnOffTune,
	&delayBeginYear,
	&delayBeginMonth,
	&delayBeginDate,
	&delayBeginHour,
	&delayBeginMinute);

DateControl delayEndControl("Отлож. стоп:",
	&delayBeginOnOffTune,
	&delayBeginYear,
	&delayBeginMonth,
	&delayBeginDate,
	&delayBeginHour,
	&delayBeginMinute);

MotionControl motionControl("Контр. движ.:",
	&MotionControlOnOffTune,
	&OnIfMotionPeriod,
	&IRMSensorsTune);

SensorsSocketsControl airTempContr("Темпер. возд.:", 
	&airTempControlOnOffTune,
	&airTempControlSensors,
	&airTempControlUpSockets,
	&airTempControlDownSockets,
	&airTempControlTimeProfile,
	createAirTempTimeProfile
);

SensorsSocketsControl batTempContr("Темпер. бат.:",
	&batTempControlOnOffTune,
	&batTempControlSensors,
	&batTempControlUpSockets,
	&batTempControlDownSockets,
	&batTempControlTimeProfile,
	createBatTempTimeProfile);

SensorsSocketsControl coContr("Уровень CO:",
	&coControlOnOffTune,
	&COControlSensors,
	&COControlUpSockets,
	&COControlDownSockets,
	&COControlTimeProfile,
	createLightTimeProfile);

SensorsSocketsControl lightControl("Освещение:",
	&lightControlOnOffTune,
	&lightControlSensors,
	&lightControlUpSockets,
	&lightControlDownSockets,
	&lightControlTimeProfile,
	createLightTimeProfile);*/

//SensorsSocketsControl dryingTempContr("Темпер. сушки.:", &dryingTempOnOffTune, dryingTempControlSocketsV, &dryingTempProfileIndex, dryingTempProfiles, dryingTermistorsV);
//SensorsSocketsControl dryingHumidityContr("Влажн. сушки.:", &dryingHumidityOnOffTune, dryingHumidityControlSocketsV, HumiditySensorsV, &humiditiNullLevelTune);
//SensorsSocketsControl mashingControl("Температ. паузы:", &MashingOnOffTune, mashingSocketsV, MashingPausesV, mashTermistorsV);
//SensorsSocketsControl boilingControl("Варка пива:", &BoilingOnOffTune, boilingSocketsV, BoilingPausesV, boilTermistorsV);
//MixControl pumpControl("Насос:", &PumpOnOffTune, pumpSocketsV, &PumpMode, mashingSocketsV);
//MixControl dryingVentControl("Вентилятор:", &dryingVentOnOffTune, dryingVentSocketsV, &dryingVentMode, dryingTempControlSocketsV);
//PCounterControl dayPCounter("Счетчик ДЕНЬ", &dayPCounterOnOffTune, BaseUnitSocketsV, dayPCounterFirstByte.FlashAddress, 7, 0, 23, 0);
//PCounterControl nightPCounter("Счетчик НОЧЬ", &nightPCounterOnOffTune, BaseUnitSocketsV, nightPCounterFirstByte.FlashAddress, 23, 1, 6, 59);

/*std::vector<ControlBase *> Controls = { 
	&delayBeginControl,
	&delayEndControl,
	&motionControl,
	&airTempContr,
	&batTempContr,
	//&dryingTempContr,
	//&dryingHumidityContr,
	&coContr,
	&lightControl,
	//&mashingControl,
	//&boilingControl,
	//&pumpControl,
	//&dryingVentControl,
	//&dayPCounter,
	//&nightPCounter	
};*/

/*void ControlObjectsInit()
{
	uint8_t counter = 0;
	for (auto control : Controls)
	{
		control->init(counter);
		counter++;
	}
}*/