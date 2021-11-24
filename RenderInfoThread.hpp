#pragma once

#include "FreeRTOS.h"
#include "thread.hpp"
#include "ticks.hpp"
#include "task.h"
#include "Auxiliary.h"
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
			
			
			for (auto element : Info_Screen)
				element->Render();
			
			TickType_t ticks = Ticks::SecondsToTicks(DelayInSeconds);
			if (ticks)
				DelayUntil(ticks);
			
		}
	}
	;
};

