#include "FreeRTOS.h"
#include "thread.hpp"
#include "ticks.hpp"
#include "task.h"
#include "adc.h"
#include <vector>
#include "ADCDevObjects.hpp"
#include "SensorObjectsExt.hpp"

//extern std::vector<ADCDev*> ADCDevs;

using namespace cpp_freertos;
using namespace std;


class getADCVols : public Thread {

public:

	getADCVols(string name, 
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
			//xSemaphoreTake(lcdmut_handle, portMAX_DELAY);
			
			HAL_ADCEx_InjectedStart(&hadc1);		
			HAL_ADC_PollForConversion(&hadc1, 100);
			
			uint32_t R1_Val = HAL_ADCEx_InjectedGetValue(&hadc1, ADC_INJECTED_RANK_1);
			ADCDevises[0]->addAdcResult(R1_Val);   //CO
			uint32_t R2_Val = HAL_ADCEx_InjectedGetValue(&hadc1, ADC_INJECTED_RANK_2);
			ADCDevises[1]->addAdcResult(R2_Val);   //termistor 1
			uint32_t R3_Val = HAL_ADCEx_InjectedGetValue(&hadc1, ADC_INJECTED_RANK_3);
			ADCDevises[2]->addAdcResult(R3_Val);    //termistor 2
			uint32_t R4_Val = HAL_ADCEx_InjectedGetValue(&hadc1, ADC_INJECTED_RANK_4);
			ADCDevises[3]->addAdcResult(R4_Val);    //light sens

			HAL_ADCEx_InjectedStop(&hadc1);
			
			IRMSensor->ExecuteStep();
			
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

