#include "FreeRTOS.h"
#include "thread.hpp"
#include "ticks.hpp"
#include "task.h"
#include "usart.h"

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
			//uint8_t strgmr[] = "AT+GMR\r\n";
			//HAL_UART_Transmit(&huart1, strgmr, sizeof(strgmr), 0xFF);
			
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
			uint8_t fchar = 0;
			
			uint8_t strout[200] = { 0 };
			HAL_UART_Receive(&huart1, (uint8_t *)&strout, 200, 0xFF);

			if (strout[0] != 0)
			{
				fchar = strout[0];
			}
			
			if (strout[1] != 0)
			{
				fchar = strout[1];
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

//USARTTransmit usartt("usartt", 6, 1, 5);
//USARTResive usartr("usartr", 7, 1, 6);
