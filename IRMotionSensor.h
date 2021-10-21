#pragma once
#include "main.h"
#define IR_MOTION_BUFFER_SIZE 480
#define BUFFER_STEPS_PERIOD 60

class IRMotionSensor
{
public:
	IRMotionSensor(const char* name,
		GPIO_TypeDef* gPIOx,
		uint16_t gPIO_Pin);
	IRMotionSensor(const char* name, 
		GPIO_TypeDef* gPIOx, 
		uint16_t gPIO_Pin,
		uint16_t stepsInBufferElement);
	
	char Name[40];
	void ExecuteStep();
	uint32_t stepsAfterLastDetection = 0;	
	uint16_t motionsDetected(uint16_t bufferElementsQuant);

private:
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
	uint8_t buffer[IR_MOTION_BUFFER_SIZE] = { 0 };
	uint16_t bufferPtr = 0 ;
	uint16_t StepsInBufferElement = 60;
	uint16_t currentBufferElementStep = 0;
	
};
