#pragma once

#include "FreeRTOS.h"
#include "thread.hpp"
#include "ticks.hpp"
#include "task.h"
#include "usart.h"
#include "UsartObjectsExt.hpp"
#include "main.h"

extern SemaphoreHandle_t usart_handle;

using namespace cpp_freertos;
using namespace std;

class USARTTransmit : public Thread {

public:

	USARTTransmit(const char* name, 
		int i, 
		int delayInSeconds,
		UBaseType_t Priority)
							
		: Thread(name, 100, Priority)
		, id (i)
		, DelayInSeconds(delayInSeconds)
	{
		Start();
	}
	;

protected:

	virtual void Run() {
		while (true)
		{
			if (usartData.size() > 0)
			{
				xSemaphoreTake(usart_handle, portMAX_DELAY);
				
				HAL_UART_Transmit(&huart1, usartData.back(), usartLenght.back(), 0xFF);
				
				usartData.pop_back();
				usartLenght.pop_back();

				xSemaphoreGive(usart_handle);
			}
			
			TickType_t ticks = Ticks::SecondsToTicks(DelayInSeconds);
			if (ticks)
				DelayUntil(ticks);
			
		}
	}
	;
private:
	int id;
	int DelayInSeconds;
};

class USARTResive : public Thread {

public:

	USARTResive(const char* name, 
		int i, 
		int delayInSeconds,
		UBaseType_t Priority)
							
		: Thread(name, 100, Priority)
		, id (i)
		, DelayInSeconds(delayInSeconds)
	{
		Start();
	}
	;

protected:

	virtual void Run() {
		while (true)
		{
			
			uint8_t strout[200] = { 0 };
			HAL_UART_Receive(&huart1, (uint8_t *)&strout, 200, 0xFF);
			
			TickType_t ticks = Ticks::SecondsToTicks(DelayInSeconds);
			if (ticks)
				DelayUntil(ticks);
			
		}
	}
	;
private:
	int id;
	int DelayInSeconds;
};
