#include "TuneObjectsExt.hpp"
#include "DateControl.hpp"
#include "MotionControl.hpp"
#include "MixControl.hpp"
#include "TimeProfiles.hpp"
#include <vector>
#include "Control.hpp"
#include "PCounterControl.hpp"

DateControl delayBeginControl("Отлож. старт:", &delayBeginOnOffTune, &delayBegin);
DateControl delayEndControl("Отлож. стоп:", &delayEndOnOffTune, &delayEnd);
MotionControl motionControl("Контр. движ.:", &MotionControlOnOffTune, &OnIfMotionPeriod, IRMSensorsV);
TempControl airTempContr("Темпер. возд.:", &airTempControlOnOffTune, airTempControlSocketsV, &airTempProfileIndex, airTProfiles, airTermistorsV);
TempControl batTempContr("Темпер. бат.:", &batTempControlOnOffTune, batTempControlSocketsV, &batTempProfileIndex, batTProfiles, batTermistorsV);
TempControl dryingTempContr("Темпер. сушки.:", &dryingTempOnOffTune, dryingTempControlSocketsV, &dryingTempProfileIndex, dryingTempProfiles, dryingTermistorsV);
HumidityControl dryingHumidityContr("Влажн. сушки.:", &dryingHumidityOnOffTune, dryingHumidityControlSocketsV, HumiditySensorsV, &humiditiNullLevelTune);
COControl coContr("Уровень CO:", &coControlOnOffTune, airQualityControlSocketsV, COSensorsV, &CONullLevel);
LightControl lightControl("Освещение:", &lightControlOnOffTune, lightSocketsV, &LightProfileIndex, &LightSwitchOffDelay, lightEdgeProfiles, lightSensorsV);
MashingControl mashingControl("Температ. паузы:", &MashingOnOffTune, mashingSocketsV, MashingPausesV, mashTermistorsV);
BoilingControl boilingControl("Варка пива:", &BoilingOnOffTune, boilingSocketsV, BoilingPausesV, boilTermistorsV);
MixControl pumpControl("Насос:", &PumpOnOffTune, pumpSocketsV, &PumpMode, mashingSocketsV);
MixControl dryingVentControl("Вентилятор:", &dryingVentOnOffTune, dryingVentSocketsV, &dryingVentMode, dryingTempControlSocketsV);
PCounterControl dayPCounter("Счетчик ДЕНЬ", &dayPCounterOnOffTune, BaseUnitSocketsV, dayPCounterFirstByte.FlashAddress, 7, 0, 23, 0);
PCounterControl nightPCounter("Счетчик НОЧЬ", &nightPCounterOnOffTune, BaseUnitSocketsV, nightPCounterFirstByte.FlashAddress, 23, 1, 6, 59);

std::vector<ControlBase *> Controls = { 
	&delayBeginControl,
	&delayEndControl,
	&motionControl,
	&airTempContr,
	&batTempContr,
	&dryingTempContr,
	&dryingHumidityContr,
	&coContr,
	&lightControl,
	&mashingControl,
	&boilingControl,
	&pumpControl,
	&dryingVentControl,
	&dayPCounter,
	&nightPCounter	
};

void ControlObjectsInit()
{
	uint8_t counter = 0;
	for (auto control : Controls)
	{
		control->init(counter);
		counter++;
	}
}