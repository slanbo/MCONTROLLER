#include "MQ7.hpp"

MQ7::MQ7(uint16_t ID, std::string name, uint8_t ADCDevID)
	: ADCSensor(ID, name, ADCDevID, CO_SENSOR_TYPE_INDEX) 
{
}



