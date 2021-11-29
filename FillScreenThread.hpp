#include "FreeRTOS.h"
#include "thread.hpp"
#include "ticks.hpp"
#include "task.h"
#include "ModeObjectsExt.hpp"
#include "Auxiliary.h"
#include "string.h"
#include "ScreenObjectsExt.hpp"
#include "MenuClass.hpp"


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
			xSemaphoreTake(lcdmut_handle, portMAX_DELAY);
					strcpy(prefixStr, "");
					addCurrentDateString(prefixStr);
					Date_FirstPart->SetText(prefixStr, true);

					strcpy(prefixStr, "");
					addCurrentTimeString(prefixStr);
					Time->SetText(prefixStr, false);
			
					if (SETUP_MODE == 0)
					{
				
						Buttom_Left->SetText("Меню", true);
						Buttom_Right->SetText("Меню", true);
					}
					else
					{
						Buttom_Left->SetText("Вверх", true);
						Buttom_Right->SetText("Вниз", true);
					}
			
					for (auto element : TopBottom_FirstScreen)
						element->Render();
			
					if (SETUP_MODE == 1)
					{
						mainMenu->FillScreen();
						//for (auto element : Menu_Screen)
						//	element->Render();
						
						Menu_Header->Render();
						Menu_SubHeader->Render();
						Menu_PrevString->Render();
						Menu_CurrentString->Render();
						Menu_NextString->Render();
						Menu_CurrentScreen_Border->Render();
						Menu_Header_Border->Render();
						
					}
			xSemaphoreGive(lcdmut_handle); 
			

			TickType_t ticks = Ticks::SecondsToTicks(DelayInSeconds);
			if (ticks)
				DelayUntil(ticks);
			
		}
	}
	;
	

};
