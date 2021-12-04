#ifndef _SENSOROBJECTSEXT__H
#define _SENSOROBJECTSEXT__H

#include "Sensors.hpp"

extern MQ7* COSens;
extern NTC_10K_B3950* Termistor_1;
extern NTC_10K_B3950* Termistor_2;
extern LightSensor* lightSensor;
extern ADCSensor humiditySensor;

extern std::vector<ADCSensor*> ADCSensorsV;

//IR MOTION SENSOR

extern IRMotionSensor*  IRMSensor;
extern std::vector<IRMotionSensor*> IRMotionSensorsV;

#endif