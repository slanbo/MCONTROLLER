#include "LightSensor.h"

LightSensor::LightSensor(uint16_t ID, std::string name, uint8_t ADCDevID)
	: ADCSensor(ID, name, ADCDevID)
{
}
