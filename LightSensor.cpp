#include "LightSensor.hpp"

LightSensor::LightSensor(uint16_t ID, std::string name, uint8_t ADCDevID)
	: ADCSensor(ID, name, ADCDevID, LIGHT_SENSOR_TYPE_INDEX)
{
	UNITS[0] = 'L';
	UNITS[1] = 'X';
	UNITS[2] = ' ';
	UNITS[3] = 0;
	
}
