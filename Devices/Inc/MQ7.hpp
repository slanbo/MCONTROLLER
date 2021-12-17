#ifndef __MQ7__H
#define __MQ7__H

#include "gpio.h"
#include "adc.h"
#include "ADCSensorDev.hpp"

#define MQ7_ONE_PPM 10

class MQ7 : public ADCSensor
{
private:
public:
	
	MQ7(uint16_t ID, const char* name, uint8_t ADCDevID);
	virtual uint16_t getSensorUnits();
		
};

#endif


