#include "FreeRTOS.h"
#include "thread.hpp"
#include "ticks.hpp"
#include "task.h"
#include "PCounters.hpp"

using namespace cpp_freertos;
using namespace std;

class PCountersExecuteStep : public Thread {

public:

	PCountersExecuteStep(string name, 
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
		
			//dayPCounter.ExecuteStep();
			//nightPCounter.ExecuteStep();
			
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

