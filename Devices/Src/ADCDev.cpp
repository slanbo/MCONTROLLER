#include "ADCDev.hpp"
#include "Auxiliary.hpp"
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"

ADCDev::ADCDev(uint16_t id, std::string name) : BaseObject(id, name)
{
}
;

uint16_t ADCDev::getMinVol()
{
	uint16_t minValue = 0;
	for (uint8_t i = 0; i < MAX_RESULTS_ARRAY; i++)
	{
		if (adcResults[i] == 0 | adcResults[i] <= minValue)
		{
			minValue = adcResults[i];
		}
	}
	return minValue;
	
}


uint16_t ADCDev::getMaxVol()
{
	uint16_t maxValue = 0;
	for (uint8_t i = 0; i < MAX_RESULTS_ARRAY; i++)
	{
		if (adcResults[i] >= maxValue)
		{
			maxValue = adcResults[i];
		}
	}
	return maxValue;
}


void ADCDev::shiftAdcResultArray()
{
	for (uint8_t i = MAX_RESULTS_ARRAY - 1; i > 0; i--)
	{
		adcResults[i] = adcResults[i - 1];
	}
}

uint16_t ADCDev::getAverageAdcResult()
{
	uint16_t maxValue = getMaxVol();
	uint16_t minValue = getMinVol();
	
	uint8_t valCounter = 0;
	uint16_t sum = 0;
	
	if (maxValue == minValue)
	{
		return maxValue;
	}
	
	for (uint8_t i = 0; i < MAX_RESULTS_ARRAY - 1; i++)
	{
		if (adcResults[i] != maxValue & adcResults[i] != minValue & adcResults[i] != 0)
		{
			sum += adcResults[i];
			valCounter += 1;
		}
	}
	
	if (valCounter == 0)
	{
		return (maxValue + minValue) / 2;
	}
	
	uint16_t averageVal = sum / valCounter;
	
	return averageVal;
}
void ADCDev::addAdcResult(uint16_t adcResult)
{
	
	shiftAdcResultArray();
	adcResults[0] = adcResult;
	
}

