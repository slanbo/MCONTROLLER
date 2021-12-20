#include "Bizzer.hpp"
#include "string.h"


Bizzer::Bizzer(const char* name, 
	GPIO_TypeDef* gPIOx, 
	uint16_t gPIO_Pin)
	: GPIOx(gPIOx)
	, GPIO_Pin(gPIO_Pin)
{
	strcpy(Name, name);
	for (uint16_t i = 0; i < BIZZER_BUFFER_SIZE; i++)
	{
		levels[i] = 255;
	}
}


void Bizzer::addLevelArray(uint8_t level)
{
	uint16_t i = 0;
	for (i = 0; i < BIZZER_BUFFER_SIZE; i++)
	{
		if (levels[i] == 255)
		{
			levels[i] = level;
			return;
		}
	}
}


void Bizzer::addHighLowLevelPeriods(uint8_t HihgLevelQuant, uint8_t LowLevelasQuant, uint8_t periods)
{
	for (uint8_t i = 0; i < periods; i++)
	{
		for (uint8_t j = 0; j < HihgLevelQuant; j++)
			addLevelArray(1);
		for(uint8_t k = 0 ; k < LowLevelasQuant ; k++)
			addLevelArray(0);
	}
}

uint8_t Bizzer::getLevelArray()
{
	uint8_t level = levels[0];
	
	if (level == 255)
	{
		return 0;
	}
	
	for (uint16_t i = 0; i < BIZZER_BUFFER_SIZE; i++)
	{
		levels[i] = levels[i + 1];
		if (levels[i] == 255)
		{
			break;
		}
	}
	return level;
}


void Bizzer::ExecuteStep()
{
	uint16_t level = getLevelArray();
	if (level == 1)
	{
		HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
	}
	
	if (level == 0)
	{
		HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);
	}
	
}
