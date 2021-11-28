#include "MQ7.hpp"

MQ7::MQ7(uint16_t ID, std::string name, uint8_t ADCDevID)
	: ADCSensor(ID, name, ADCDevID, CO_SENSOR_TYPE_INDEX) 
{
	correspondence corr_0 = { 0, 0 };
	ADCUnits.push_back(corr_0);
	
	correspondence corr_1 = { 600, 0 };
	ADCUnits.push_back(corr_1);
	
	correspondence corr_2 = { 757, 5 };
	ADCUnits.push_back(corr_2);
	
	correspondence corr_3 = { 824, 10 };
	ADCUnits.push_back(corr_3);
	
	correspondence corr_4 = { 965, 15 };
	ADCUnits.push_back(corr_4);
	
	correspondence corr_end = { 4065, 400 };
	ADCUnits.push_back(corr_end);

	UNITS[0] = 'P';
	UNITS[1] = 'P';
	UNITS[2] = 'M';
	UNITS[3] = '\0';
	
}


uint16_t MQ7::getSensorUnits()
{
	uint16_t current_ADC = adcDev->getAverageAdcResult();
	uint16_t result = getUnits(current_ADC);
	
	return result;
}
