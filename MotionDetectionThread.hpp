#include "FreeRTOS.h"
#include "thread.hpp"
#include "ticks.hpp"
#include "task.h"
#include "Sensors.hpp"

using namespace cpp_freertos;
using namespace std;


class MotionDetection : public Thread {

public:

	MotionDetection(string name, 
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

			//IRMSensor.ExecuteStep();
			
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

