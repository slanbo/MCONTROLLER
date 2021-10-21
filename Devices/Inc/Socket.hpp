#ifndef __SOCKET__H
#define __SOCKET__H

#include "Tune.hpp"
#include "BaseObject.hpp"
#include "gpio.h"

class plugSocket : public BaseObject 
{
private:
	
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
	intTune &LoadPowerVTTune;
	
public:
	
	plugSocket(uint16_t id,
		std::string name,
		GPIO_TypeDef* gPIOx,
		uint16_t gPIO_Pin,
		intTune &loadPowerVTTune);
	
	void SwitchOn();
	void SwitchOff();
	bool getSocketState();
	
	bool operator <(const plugSocket& rhs)
	{
		return LoadPowerVTTune._getVal() < rhs.LoadPowerVTTune._getVal();
	}
	
	//getters setters
	
	uint16_t getLoadpowerVT();
	void _setLoadPowerVT(uint16_t);
		
};

#endif
