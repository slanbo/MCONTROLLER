#ifndef __ADCSENSORDEV__H
#define __ADCSENSORDEV__H

#include "main.h"
#include "BaseObject.hpp"
#include <vector>
#include "ADCDev.hpp"

#define MAX_RESULTS_ARRAY 6

struct correspondence 
{
	uint16_t adcresult = 0;
	uint16_t units = 0;
};


class ADCSensor :public BaseObject
	
{
private:
	
public:
	
	ADCSensor(uint16_t ID, const char* name, uint8_t ADCDevID, uint8_t SensorTypeIndex);
	virtual uint16_t getSensorUnits();
	uint8_t sensorTypeIndex;

	char UNITS[4] = { 67, 176, 0, 0 };
	
protected:
	
	ADCDev* adcDev;
	std::vector<correspondence> ADCUnits;
	uint16_t getUnits(uint16_t adc);
	
};

#endif
