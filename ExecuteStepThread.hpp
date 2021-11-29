
#include "FreeRTOS.h"
#include "thread.hpp"
#include "ticks.hpp"
#include "task.h"
#include "ModeObjectsExt.hpp"
//#include "ADCDevObjects.hpp"


using namespace cpp_freertos;
using namespace std;

class ExecuteModeStep : public Thread {

public:

	ExecuteModeStep(string name, 
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
			
	//		xSemaphoreTake(lcdmut_handle, portMAX_DELAY);

			if (SETUP_MODE == 0)
			{
				switch (modeIndex._getVal())
				{
				case 0:
					{
						//Habitat* HabitatMode = (Habitat*)CurrentMode;
						//HabitatMode->ExecuteStep();
						//break;
					}
				default:
					{
						//Habitat* HabitatMode = (Habitat*)CurrentMode;
						//HabitatMode->ExecuteStep();
						//break;
					}
				}
				;
				
			HabitatMode->ExecuteStep();
				
			}
			
			//xSemaphoreGive(lcdmut_handle); 
			
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

