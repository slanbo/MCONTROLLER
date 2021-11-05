#pragma once
#include "gpio.h"
#include "adc.h"
#include "ADCSensorDev.hpp"

#define MQ7_ONE_PPM 10


class MQ7 : public ADCSensor
{
private:
	
public:
	
	MQ7(uint16_t ID, std::string name, uint8_t ADCDevID);
	
	
		
};




