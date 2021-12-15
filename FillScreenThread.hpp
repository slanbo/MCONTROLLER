#include "FreeRTOS.h"
#include "thread.hpp"
#include "ticks.hpp"
#include "task.h"
#include "ModeObjectsExt.hpp"
#include "Auxiliary.hpp"
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
			RTC_TimeTypeDef sTime = { 0 };
			RTC_DateTypeDef sDate = { 0 };
			HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
			HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	
			Date_FirstPart->ClearText();
			Date_FirstPart->SetIntText(sDate.Date, 2, '0');
			Date_FirstPart->SetChars("/", false);
			Date_FirstPart->SetIntText(sDate.Month, 2, '0');
			Date_FirstPart->SetChars("/", false);
			Date_FirstPart->SetIntText(sDate.Year, 2, '0');
			Date_FirstPart->SetChars("/", false);
			switch (sDate.WeekDay)
			{
			case 1:
				{
					Date_FirstPart->SetChars("ВС", true);
					break;
				}
			case 2:
				{
					Date_FirstPart->SetChars("ПН", true);
					break;
				}	
			case 3:
				{
					Date_FirstPart->SetChars("ВТ", true);
					break;
				}	
			case 4:
				{
					Date_FirstPart->SetChars("СР", true);
					break;
				}
			case 5:
				{
					Date_FirstPart->SetChars("ЧТ", true);
					break;
				}
			case 6:
				{
					Date_FirstPart->SetChars("ПТ", true);
					break;
				}	
			case 7:
				{
					Date_FirstPart->SetChars("СБ", true);
					break;
				}	
		
			}
			Date_FirstPart->_setUpdated(true);

			Time->ClearText();
			Time->SetIntText(sTime.Hours, 2, '0');
			Time->SetChars(":", false);
			Time->SetIntText(sTime.Minutes, 2, '0');
			Time->SetChars(":", false);
			Time->SetIntText(sTime.Seconds, 2, '0');
			Time->_setUpdated(true);
			
			if (SETUP_MODE == 0)
			{
				if (showInfoCounter == 0)
				{
					bool screenFilled = false;
					if (!Modes.at(modeIndex._getVal())->allscreensfilled) 
					{
						ControlsMode* mode  = Modes.at(modeIndex._getVal());
						mode->FillScreen();
						screenFilled = true;
					}
					if (!screenFilled)
					{
						PCountersVector.at(currentPCounter)->FillScreen();
						currentPCounter++;
						if (currentPCounter == PCountersVector.size())
						{
							currentPCounter = 0;
							Modes.at(modeIndex._getVal())->allscreensfilled = false;	
						}
					}
				}
			
				showInfoCounter++;
				if (showInfoCounter == SHOW_INFO_PERIOD_SEC)
					showInfoCounter = 0;
				
				Buttom_Left->ClearText();
				Buttom_Left->SetChars("Меню", true);
				Buttom_Left->_setUpdated(true);
				
				Buttom_Right->ClearText();
				Buttom_Right->SetChars("Меню", true);
				Buttom_Right->_setUpdated(true);
				
			}
			else
			{
				mainMenu->FillScreen();
				
				Buttom_Left->ClearText();
				Buttom_Left->SetChars("Вверх", true);
				Buttom_Left->_setUpdated(true);
				
				Buttom_Right->ClearText();
				Buttom_Right->SetChars("Вниз ", true);
				Buttom_Right->_setUpdated(true);
			}
			
			TickType_t ticks = Ticks::SecondsToTicks(DelayInSeconds);
			if (ticks)
				DelayUntil(ticks);
			
		}
	}
	;
};
