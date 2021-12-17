#pragma once
#include "main.h"
#include "ADCSensorDev.hpp"

class LightSensor : public ADCSensor
{
public:
	LightSensor(uint16_t ID, const char* name, uint8_t ADCDevID);
private:
	
};
