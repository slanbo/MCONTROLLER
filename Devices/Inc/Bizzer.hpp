#pragma once
#include "gpio.h"

#define BIZZER_BUFFER_SIZE 50

class Bizzer
{
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
	
	uint8_t levels[BIZZER_BUFFER_SIZE] = { 0 };
	
public:
	
	char Name[16];
	Bizzer(const char* name, GPIO_TypeDef* gPIOx, uint16_t gPIO_Pin);
	void ExecuteStep();
	void addLevelArray(uint8_t level);
	uint8_t getLevelArray();
};