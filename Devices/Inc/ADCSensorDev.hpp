#pragma once
#include "main.h"
#include "BaseObject.hpp"
#include  <string>
#include "ADCDev.hpp"

#define MAX_RESULTS_ARRAY 6



class ADCSensor :public BaseObject
	
{
private:
	
public:
	
	ADCSensor(uint16_t ID, std::string name, uint8_t ADCDevID, uint8_t SensorTypeIndex);
	virtual uint16_t getSensorUnits();
	uint8_t sensorTypeIndex;

protected:
	
	ADCDev* adcDev;
	

};


