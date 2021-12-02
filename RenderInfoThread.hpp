#pragma once

#include "FreeRTOS.h"
#include "thread.hpp"
#include "ticks.hpp"
#include "task.h"
#include "Auxiliary.h"
#include "ScreenObjectsExt.hpp"
#include "string.h"

extern uint8_t showInfoCounter;
	
using namespace cpp_freertos;
using namespace std;


class RenderInfoScreen : public Thread {

public:

	RenderInfoScreen(string name, 
		int i, 
		int delayInSeconds, 
		UBaseType_t Priority)
		: Thread(name, 100, Priority)
		, id(i)
		, DelayInSeconds(delayInSeconds)
		
	{
		Start();
	}
	;
	
private:
	int id;
	int DelayInSeconds;	
	
protected:

	virtual void Run()
	{
		while (true)
		{
			xSemaphoreTake(lcdmut_handle, portMAX_DELAY);
			
			for (auto element : TopBottom_FirstScreen)
				element->Render();
			
			if (SETUP_MODE == 0)
			{
				if (showInfoCounter == 0)
				{
					HabitatMode->FillScreen();
					Info_Header->Render();
					Info_Header_Border->Render();
					Info_SubHeader->Render();
					Info_FirstString->Render();
					Info_SecondString->Render();
					Info_ThirdString->Render();
					Info_FourthString->Render();
				}
			}
			
			showInfoCounter++;
			if (showInfoCounter == SHOW_INFO_PERIOD_SEC)
				showInfoCounter = 0;
			
			xSemaphoreGive(lcdmut_handle); 
			
			TickType_t ticks = Ticks::SecondsToTicks(DelayInSeconds);
			if (ticks)
				DelayUntil(ticks);
			
		}
	}
	;
};

