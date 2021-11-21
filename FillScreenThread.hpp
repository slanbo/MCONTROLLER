#include "FreeRTOS.h"
#include "thread.hpp"
#include "ticks.hpp"
#include "task.h"
#include "ModeObjectsExt.hpp"


using namespace cpp_freertos;
using namespace std;

class FillScreen : public Thread {

public:

	FillScreen(string name, 
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
			strcpy(prefixStr, "");
			addCurrentDateString(prefixStr);
			Date_FirstPart.SetText(prefixStr, true);
			
			strcpy(prefixStr, "");
			addCurrentTimeString(prefixStr);
			Time.SetText(prefixStr, false);
			
			Buttom_Left.SetText("Меню", true);
			Buttom_Right.SetText("Меню", true);
			
			HabitatMode.FillScreen();
			
			
			
			TickType_t ticks = Ticks::SecondsToTicks(DelayInSeconds);
			if (ticks)
				DelayUntil(ticks);
			
		}
	}
	;
	

};
