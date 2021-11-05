#pragma once
#ifndef _SENSOROBJECTS__H
#define _SENSOROBJECTS__H

//#include <vector>
#include "Sensors.hpp"

// ################## ADC Devs

//++++++++++ SENSORS +++++++++++++++++++

//CO SENSOR
MQ7 COSens(1, "MQ7", 1);
NTC_10K_B3950 Termistor_1(2 ,"TSENSOR 1", 2);
NTC_10K_B3950 Termistor_2(3, "TSENSOR 2", 3);
LightSensor lightSensor(4, "LIGHT SENSOR ", 4);
ADCSensor humiditySensor(5, "HUMIDITY", 4);

std::vector<ADCSensor*> ADCSensorsV = { &COSens, &Termistor_1, &Termistor_2, &lightSensor, &humiditySensor};


//IR MOTION SENSOR

char IRMSensorName[16] = "IRM SENSOR ";
IRMotionSensor  IRMSensor(IRMSensorName, IR_MOTION_SENSOR_GPIO_Port, IR_MOTION_SENSOR_Pin);
std::vector<IRMotionSensor*> IRMotionSensorsV = { &IRMSensor };

#endif