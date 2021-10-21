#ifndef __SENSORS__H
#define __SENSORS__H
	
#include "NTC_10K_B3950.hpp"	
#include "MQ7.h"
#include "IRMotionSensor.h"
#include "LightSensor.h"
#include <vector>
	
#define AIR_TERMISTOR_QUANTITY 1
#define BAT_TERMISTOR_QUANTITY 1
#define IRM_SENSORS_QUANTITY 1
#define LIGHT_SENSORS_QUANTITY 1
#define MASH_SENSORS_QUANTITY 2
#define BOIL_SENSORS_QUANTITY 2
	
	
	extern MQ7 COSens;
	extern NTC_10K_B3950 Termistor_1;
	extern NTC_10K_B3950 Termistor_2;
	extern IRMotionSensor  IRMSensor;
	extern LightSensor lightSensor;
	
	extern std::vector<ADCSensor*> ADCSensorsV;


#endif