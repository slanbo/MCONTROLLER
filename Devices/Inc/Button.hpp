#ifndef __BUTTON__H
#define __BUTTON__H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "gpio.h"

class Button
{
private:
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
	double* ptr_ms_Pressed;
public:
	
	char Name[16];
	Button(const char* name) ;
	void EndButtonPressProcess();
	/*void processDateTimeChange();
	void fillCurrentDateTimeToCurrentSettings();
	void processRestoreDefaults();
	void fillSocketPowerCurrentSettings();
	void processPowerChange();*/
	
	
};
	
#ifdef __cplusplus
}
#endif
#endif