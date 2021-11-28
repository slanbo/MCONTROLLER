#include "ADCSensorDev.hpp"
#include "string.h"
#include "BaseObject.hpp"
#include "vector"
#include <cassert>
#include "ADCDevObjectsExt.hpp"



ADCSensor::ADCSensor(uint16_t ID, std::string name, uint8_t ADCDevID, uint8_t SensorTypeIndex)
	: BaseObject(ID, name),
	sensorTypeIndex(SensorTypeIndex)
{
	for (auto dev : ADCDevises)
		if (dev->_getId() == ADCDevID)
			adcDev = dev;
	
	
}

uint16_t ADCSensor::getSensorUnits()
{
	assert(adcDev != nullptr);
	return adcDev->getAverageAdcResult();
}


uint16_t ADCSensor::getUnits(uint16_t adc)
{
	uint8_t i = 0;
	for (correspondence element : ADCUnits)
		{
			if (element.adcresult == adc)
				return element.units;
			else if (element.adcresult > adc)
			{
				uint16_t beforeunits = ADCUnits.at(i - 1).units;
				uint16_t adcelementsdelta = element.adcresult - ADCUnits.at(i - 1).adcresult;
				uint16_t unitselementsdelta = element.units - ADCUnits.at(i - 1).units;
				uint16_t adcsdelta = adc - ADCUnits.at(i - 1).adcresult;
				uint16_t result = (uint16_t)(beforeunits + unitselementsdelta*((double)adcsdelta / adcelementsdelta));
				
				return result;
			}
			i++;
		}
	return 0;
	}
