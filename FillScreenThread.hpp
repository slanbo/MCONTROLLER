#include "FreeRTOS.h"
#include "thread.hpp"
#include "ticks.hpp"
#include "task.h"
#include "ModeObjectsExt.hpp"
#include "Auxiliary.h"
#include "string.h"
#include "ScreenObjectsExt.hpp"
#include "MenuClass.hpp"
#include "PCounterObjectsExt.hpp"

extern uint8_t showInfoCounter;
extern uint8_t currentPCounter;


using namespace cpp_freertos;
using namespace std;

extern Menu* mainMenu;

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
			char dateStr[11] = { 0 };
			addCurrentDateString(dateStr);
			Date_FirstPart->ClearText();
			Date_FirstPart->SetText(dateStr, true);
			Date_FirstPart->_setUpdated(true);

			char timeStr[8] = { 0 };
			addCurrentTimeString(timeStr);
			Time->ClearText();
			Time->SetText(timeStr, false);
			Time->_setUpdated(true);
			
			if (SETUP_MODE == 0)
			{
				
				if (showInfoCounter == 0)
				{
					if (!HabitatMode->allscreensfilled)
						HabitatMode->FillScreen();
					else
					{
						PCountersVector.at(currentPCounter)->FillScreen();
						currentPCounter++;
						if (currentPCounter == PCountersVector.size())
							HabitatMode->allscreensfilled = false;	
					}
						
				}
			
				showInfoCounter++;
				if (showInfoCounter == SHOW_INFO_PERIOD_SEC)
					showInfoCounter = 0;
				
				Buttom_Left->ClearText();
				Buttom_Left->SetText("Меню", true);
				Buttom_Left->_setUpdated(true);
				
				Buttom_Right->ClearText();
				Buttom_Right->SetText("Меню", true);
				Buttom_Right->_setUpdated(true);
				
			}
			else
			{
				mainMenu->FillScreen();
				
				Buttom_Left->ClearText();
				Buttom_Left->SetText("Вверх", true);
				Buttom_Left->_setUpdated(true);
				
				Buttom_Right->ClearText();
				Buttom_Right->SetText("Вниз", true);
				Buttom_Right->_setUpdated(true);
			}
			
			TickType_t ticks = Ticks::SecondsToTicks(DelayInSeconds);
			if (ticks)
				DelayUntil(ticks);
			
		}
	}
	;
};
