#pragma once
#ifndef _SENSOROBJECTS__H
#define _SENSOROBJECTS__H

//#include <vector>
#include "Sensors.hpp"

// ################## ADC Devs
//++++++++++ SENSORS +++++++++++++++++++

//CO SENSOR
MQ7* COSens = new MQ7(1, "MQ7", 1);
NTC_10K_B3950* Termistor_1 = new NTC_10K_B3950(2, "TSENSOR 1", 2);
NTC_10K_B3950* Termistor_2 = new NTC_10K_B3950(3, "TSENSOR 2", 3);
LightSensor* lightSensor = new LightSensor(4, "LIGHT SENSOR ", 4);

//ADCSensor* humiditySensor = new ADCSensor(5, "HUMIDITY", 4, HUMIDITY_SENSOR_TYPE_INDEX);

std::vector<ADCSensor*> ADCSensorsV = { COSens, Termistor_1, Termistor_2, lightSensor};


//IR MOTION SENSOR

char IRMSensorName[16] = "IRM SENSOR ";
IRMotionSensor* IRMSensor  = new IRMotionSensor(1, IRMSensorName, IR_MOTION_SENSOR_GPIO_Port, IR_MOTION_SENSOR_Pin);
std::vector<IRMotionSensor*> IRMotionSensorsV = { IRMSensor };

#endif