#include "Socket.hpp"

plugSocket::plugSocket(uint16_t ID,
	const char* name,
	GPIO_TypeDef* gPIOx,
	uint16_t gPIO_Pin,
	intTune &loadPowerVTTune)
	:BaseObject(ID, name)
	, GPIOx(gPIOx)
	, GPIO_Pin(gPIO_Pin)
	, LoadPowerVTTune(loadPowerVTTune)
{
	 SwitchOff();
}

void plugSocket::SwitchOn()
{
	GPIO_PinState currState = HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);
	if (currState == GPIO_PIN_RESET)
		HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);
}


void plugSocket::SwitchOff()
{
	GPIO_PinState currState = HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);
	if (currState == GPIO_PIN_SET)
		HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
}

bool plugSocket::getSocketState()
{
	GPIO_PinState pinState = HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);
	if (pinState == GPIO_PIN_SET)
	{
		return true;
	}
	if (pinState == GPIO_PIN_RESET)
	{
		return false;
	}
	return false;
}

uint16_t plugSocket::getLoadpowerVT()
{
	return LoadPowerVTTune._getVal();
}

void plugSocket::_setLoadPowerVT(uint16_t LoadPowerVt)
{
	LoadPowerVTTune._setVal(LoadPowerVt);
	LoadPowerVTTune.save();
}
