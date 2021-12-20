
#include "FreeRTOS.h"
#include "thread.hpp"
#include "ticks.hpp"
#include "task.h"
#include "gpio.h"
#include "Bizzer.hpp"
#include "Buttons.hpp"

extern Bizzer alarmBizzer;


using namespace cpp_freertos;
using namespace std;

class menuButtonPressBizzer : public Thread {

public:

	menuButtonPressBizzer(const char* name, 
		int i, 
		int delayInTicks,
		UBaseType_t Priority)
							
		: Thread(name, 100, Priority)
		, id (i)
		, DelayInTicks(delayInTicks)
	{
		Start();
	}
	;

protected:

	virtual void Run() {
		while (true)
		{
			if (SETUP_MODE == 1)
			{
				GPIO_PinState key1State = HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin);
				if (key1State == GPIO_PIN_SET)
				{
					ticksKey1Pressed += DelayInTicks;
				}
				else
				{
					ticksKey1Pressed = 0;
				}
			
				GPIO_PinState key2state = HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin);
				if (key2state == GPIO_PIN_SET)
				{
					ticksKey2Pressed += DelayInTicks;
				}
				else
				{
					ticksKey2Pressed = 0;
				}
			
				
				if (ticksKey1Pressed >= FIRST_PRESSING_EDGE_MS & ticksKey1Pressed <= FIRST_PRESSING_EDGE_MS + DelayInTicks - 1)
				{
					alarmBizzer.addHighLowLevelPeriods(1, 1, 1);
					}
				
				if (ticksKey2Pressed >= FIRST_PRESSING_EDGE_MS & ticksKey2Pressed <= FIRST_PRESSING_EDGE_MS + DelayInTicks - 1)
				{
					alarmBizzer.addHighLowLevelPeriods(1, 1, 1);
				}
				
				if (ticksKey1Pressed >= SECOND_PRESSING_EDGE_MS & ticksKey1Pressed <= SECOND_PRESSING_EDGE_MS + DelayInTicks - 1)
				{
					alarmBizzer.addHighLowLevelPeriods(1, 1, 2);
				}
				
				if (ticksKey2Pressed >= SECOND_PRESSING_EDGE_MS & ticksKey2Pressed <= SECOND_PRESSING_EDGE_MS + DelayInTicks - 1)
				{
					alarmBizzer.addHighLowLevelPeriods(1, 1, 2);
				}
			}
			
			
			if (DelayInTicks)
				DelayUntil(DelayInTicks);
		}
	}
	;
	
private:
	int id;
	int DelayInTicks;
};


class bizzerExecuteStep : public Thread {

public:

	bizzerExecuteStep(const char* name, 
		int i, 
		int delayInTicks,
		UBaseType_t Priority)
							
		: Thread(name, 100, Priority)
		, id (i)
		, DelayInTicks(delayInTicks)
	{
		Start();
	}
	;

protected:

	virtual void Run() {
		while (true)
		{
			
			alarmBizzer.ExecuteStep();
			
			if (DelayInTicks)
				DelayUntil(DelayInTicks);
		}
	}
	;
	
private:
	int id;
	int DelayInTicks;
};

