#pragma once

#include "FreeRTOS.h"
#include "thread.hpp"
#include "ticks.hpp"
#include "task.h"
#include "Auxiliary.hpp"
#include "ScreenObjectsExt.hpp"
#include "string.h"

	
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
			//xSemaphoreTake(lcdmut_handle, portMAX_DELAY);
			
			for (auto element : TopBottom_FirstScreen)
				element->Render();
			
			if (SETUP_MODE == 0)
			{
				Info_Header->Render();
				Info_Header_Border->Render();
				Info_SubHeader->Render();
				Info_FirstString->Render();
				Info_SecondString->Render();
				Info_ThirdString->Render();
				Info_FourthString->Render();
			}
			else
			{
				Menu_Header->Render();
				Menu_SubHeader->Render();
				Menu_PrevString->Render();
				Menu_CurrentString->Render();
				Menu_NextString->Render();
				Menu_CurrentScreen_Border->Render();
				Menu_Header_Border->Render();
			}
			
			
			//xSemaphoreGive(lcdmut_handle); 
			
			TickType_t ticks = Ticks::SecondsToTicks(DelayInSeconds);
			if (ticks)
				DelayUntil(ticks);
			
		}
	}
	;
};

