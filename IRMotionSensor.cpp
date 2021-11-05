#include "IRMotionSensor.hpp"
#include "string.h"

void IRMotionSensor::ExecuteStep()
{
	GPIO_PinState pinState = HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);
	if (pinState == GPIO_PIN_SET)
	{
		stepsAfterLastDetection = 0;
		if (buffer[bufferPtr] <= 0xff)
			buffer[bufferPtr] += 1;
	}
	else
	{
		stepsAfterLastDetection += 1;
	}
	
	currentBufferElementStep += 1;
	if (currentBufferElementStep <= StepsInBufferElement)
	{
		return;
	}
	
	currentBufferElementStep = 0;
	
	if (bufferPtr < IR_MOTION_BUFFER_SIZE)
	{
		bufferPtr += 1;
	}
	else
	{
		bufferPtr = 0;
	}
	
	buffer[bufferPtr] = 0;
	
}

IRMotionSensor::IRMotionSensor(uint16_t ID,
	const char* name, 
	GPIO_TypeDef* gPIOx, 
	uint16_t gPIO_Pin)
	: BaseObject(ID, name)
	, 
	
	GPIOx(gPIOx)
	, GPIO_Pin(gPIO_Pin)
{
}

IRMotionSensor::IRMotionSensor(uint16_t ID,
	const char* name, 
	GPIO_TypeDef* gPIOx, 
	uint16_t gPIO_Pin,
	uint16_t stepsInBufferElement)
	: BaseObject(ID, name)
	, GPIOx(gPIOx)
	, GPIO_Pin(gPIO_Pin)
	, StepsInBufferElement(stepsInBufferElement)
{
}


uint16_t IRMotionSensor::motionsDetected(uint16_t bufferElementsQuant)
{
	uint16_t motions = 0;
	uint16_t size = 0;
	uint16_t ptr = bufferPtr;
	
	if (bufferElementsQuant > IR_MOTION_BUFFER_SIZE)
	{
		size = IR_MOTION_BUFFER_SIZE;
	}
	else
	{
		size = bufferElementsQuant;
	}
	
	for (uint16_t i = 0; i < size; i++)
	{
		motions += buffer[ptr];
		if (ptr > 0)
		{
			ptr -= 1;
		}
		else
		{
			ptr =  IR_MOTION_BUFFER_SIZE;
		}
	}
	return motions;
}
;
