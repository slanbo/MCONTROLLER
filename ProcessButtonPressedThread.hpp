#include "FreeRTOS.h"
#include "thread.hpp"
#include "ticks.hpp"
#include "task.h"
#include "Buttons.hpp"
#include "MenuClass.hpp"
#include "Auxiliary.hpp"
#include "Mode.hpp"
#include "ModeObjectsExt.hpp"
#include "Bizzer.hpp"

extern Bizzer alarmBizzer;

extern Menu* mainMenu;
//extern MenuElement menuElements[MENU_ITEMS_QUANT];

using namespace cpp_freertos;
using namespace std;


class processButtonsPressed : public Thread {

public:

	processButtonsPressed(const char* name, 
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

private:
	int id;
	int DelayInSeconds;
	;	
	
protected:

	virtual void Run()
	{
		while (true)
		{
			
			//xSemaphoreTake(lcdmut_handle, portMAX_DELAY);
			bool processed = false;
			if(SETUP_MODE != 0 & bothButtonsPressCounter > 0)
			{
				SETUP_MODE = 0;
				
				set_DS_From_RTC();
				bothButtonsPressCounter -= 1;
				
				Info_Header->_setUpdated(true);
				Info_SubHeader->_setUpdated(true);
				Info_FirstString->_setUpdated(true);
				Info_SecondString->_setUpdated(true);
				Info_ThirdString->_setUpdated(true);
				Info_FourthString->_setUpdated(true);
				
				alarmBizzer.addLevelArray(1);
				alarmBizzer.addLevelArray(0);
				
				mainMenu->clearLCD();

			}
			if (SETUP_MODE != 1 & bothButtonsPressCounter > 0)
			{
				SETUP_MODE = 1;
				
				mainMenu->CurrentItemBase = &mi_0;
				BothButtons_Short_Press.processButtonPress();
				bothButtonsPressCounter -= 1;
				processed = true;
				
				alarmBizzer.addLevelArray(1);
				alarmBizzer.addLevelArray(0);
				
				mainMenu->clearLCD();

			}
			if (SETUP_MODE == 1)
			{
				if (leftButtonShortPressCounter > 0)
				{
					LeftButton_Short_Press.processButtonPress();
					leftButtonShortPressCounter -= 1;
					processed = true;
				}
				if (leftButtonLongPressCounter > 0)
				{
					LeftButton_Long_Press.processButtonPress();
					leftButtonLongPressCounter -= 1;
					processed = true;
				}
				if (leftButtonLongLongPressCounter > 0)
				{
					LeftButton_Long_Long_Press.processButtonPress();
					leftButtonLongLongPressCounter -= 1;
					processed = true;
				}
				if (rightButtonShortPressCounter > 0)
				{
					RightButton_Short_Press.processButtonPress();
					rightButtonShortPressCounter -= 1;
					processed = true;
				}
				if (rightButtonLongPressCounter > 0)
				{
					RightButton_Long_Press.processButtonPress();
					rightButtonLongPressCounter -= 1;
					processed = true;
				}
				if (rightButtonLongLongPressCounter > 0)
				{
					RightButton_Long_Long_Press.processButtonPress();
					rightButtonLongLongPressCounter -= 1;
					processed = true;
				}
			}
			else
			{
				leftButtonShortPressCounter = 0;
				leftButtonLongPressCounter = 0;
				leftButtonLongLongPressCounter = 0;
				
				rightButtonShortPressCounter = 0;
				rightButtonLongPressCounter = 0;
				rightButtonLongLongPressCounter = 0;
			}
			if (processed)
			{
				mainMenu->FillScreen();
				
				Buttom_Left->ClearText();
				Buttom_Left->SetChars("Вверх", true);
				Buttom_Left->_setUpdated(true);
				
				Buttom_Right->ClearText();
				Buttom_Right->SetChars("Вниз ", true);
				Buttom_Right->_setUpdated(true);
			}
			//xSemaphoreGive(lcdmut_handle); 
			
				
			TickType_t ticks = Ticks::SecondsToTicks(DelayInSeconds);
			if (ticks)
				DelayUntil(ticks);
		}
	};
};