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
			for (auto mode : Modes)
				mode->FillScreen();
			
			TickType_t ticks = Ticks::SecondsToTicks(DelayInSeconds);
			if (ticks)
				DelayUntil(ticks);
			
		}
	}
	;
	

};
