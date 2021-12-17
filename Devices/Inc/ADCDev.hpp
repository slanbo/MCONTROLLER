#pragma once
#include "main.h"
//#include <string>
#include "BaseObject.hpp"

#define MAX_RESULTS_ARRAY 6
#define DALAY_MIN_ADC 60000


class ADCDev : public BaseObject
{
private:
	uint16_t adcResults[MAX_RESULTS_ARRAY];
	uint16_t getMinVol();
	uint16_t getMaxVol();
	void shiftAdcResultArray();
	
public:
	
	ADCDev(uint16_t id, const char* name);
	void addAdcResult(uint16_t adcResult);
	uint16_t getAverageAdcResult();
	
};
