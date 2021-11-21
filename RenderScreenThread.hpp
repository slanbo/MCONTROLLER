#pragma once

#include "FreeRTOS.h"
#include "thread.hpp"
#include "ticks.hpp"
#include "task.h"
#include "Auxiliary.h"
//#include "ModeObjectsExt.hpp"
#include "ScreenObjectsExt.hpp"
#include "string.h"


//extern LCDMenu mainMenu;

using namespace cpp_freertos;
using namespace std;

class RenderScreen : public Thread {

public:

	RenderScreen(string name, 
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
			for (auto tbscrElement : TopBottom_FirstScreen)
				tbscrElement->Render();
			
			for (auto iscrElement : Info_Screen)
				iscrElement->Render();
			
			TickType_t ticks = Ticks::SecondsToTicks(DelayInSeconds);
			if (ticks)
				DelayUntil(ticks);
			
		}
	}
	;
};

