#include "ADCSensorDev.hpp"
#include "string.h"
#include "BaseObject.hpp"
#include "vector"
#include <cassert>
#include "ADCDevObjectsExt.hpp"



ADCSensor::ADCSensor(uint16_t ID, std::string name, uint8_t ADCDevID)
	: BaseObject(ID, name)
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
