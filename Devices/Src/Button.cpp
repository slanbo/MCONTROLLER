#include "Button.hpp"
#include "string.h"
#include "rtc.h"
#include "eeprom.h"
#include "MQ7.hpp"

extern MQ7 CO2Sens;

Button::Button(const char* name)
{
	strcpy(Name, name);
}

void Button::EndButtonPressProcess()
{
	//settingsScreen.LCD_ShowNextScreen(false);
	
}

uint8_t getIndex_bayte_arr(uint8_t val, uint8_t * arr, uint8_t size)
{
	uint8_t i;
	for (i = 0; i < size; i++)
	{
		if (arr[i] == val)
		{
			return i;
		}
	}
	return 255;
}

uint16_t getIndex_word_arr(uint16_t val, uint16_t * arr, uint8_t size)
{
	uint8_t i;
	for (i = 0; i < size; i++)
	{
		if (arr[i] == val)
		{
			return i;
		}
	}
	return 0xFFFF;
}

/*void Button::processDateTimeChange()
{
	
	if (currentSetting == YEAR_VARIANTS_INDEX  
		| currentSetting == MONTH_VARIANTS_INDEX
		| currentSetting == DATE_VARIANTS_INDEX
		| currentSetting == HOUR_VARIANTS_INDEX
		| currentSetting == MINUTE_VARIANTS_INDEX
		| currentSetting == DAY_OF_WEEK_VARIANTS_INDEX)
	{
		
		RTC_TimeTypeDef sTime = { 0 };
		RTC_DateTypeDef sDate = { 0 };

		sDate.Year = yearVariants[currentSettings[YEAR_VARIANTS_INDEX]];
		sDate.Month = monthVariants[currentSettings[MONTH_VARIANTS_INDEX]];
		sDate.Date = dateVariants[currentSettings[DATE_VARIANTS_INDEX]];
		sTime.Hours = hourVariants[currentSettings[HOUR_VARIANTS_INDEX]];
		sTime.Minutes = minuteVariants[currentSettings[MINUTE_VARIANTS_INDEX]];
		sDate.WeekDay = dayOfWeekVariants[currentSettings[DAY_OF_WEEK_VARIANTS_INDEX]];
		
		HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
		HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
		
		
	}
}

void Button::processRestoreDefaults()
{
	if (RESTORE_DEFAULTS_INDEX == currentSetting)
	{
		switch (currentSettings[RESTORE_DEFAULTS_INDEX])
		{
		case RESTORE_KVT_COUNTER_DEFAULTS_INDEX:
			{
				break;
			}
		case RESTORE_SETTINGS_DEFAULTS_INDEX:
			{
				break;
			}
		case GAS_NULL_LEVELS_INDEX:
			{
				break;
			}
		}	
	}
}



void Button::fillCurrentDateTimeToCurrentSettings()
{
	
	if (currentSetting == YEAR_VARIANTS_INDEX  
		| currentSetting == MONTH_VARIANTS_INDEX
		| currentSetting == DATE_VARIANTS_INDEX
		| currentSetting == HOUR_VARIANTS_INDEX
		| currentSetting == MINUTE_VARIANTS_INDEX
		| currentSetting == DAY_OF_WEEK_VARIANTS_INDEX)
	{
		
		RTC_TimeTypeDef sTime = { 0 };
		RTC_DateTypeDef sDate = { 0 };
		HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
		HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
		
		uint8_t index;
		
		index = getIndex_bayte_arr(sDate.Year, yearVariants, YEAR_VARIANTS_COUNT);
		currentSettings[YEAR_VARIANTS_INDEX] = index;

		index = getIndex_bayte_arr(sDate.Month, monthVariants, MONTH_VARIANTS_COUNT);
		currentSettings[MONTH_VARIANTS_INDEX] = index;
		
		index = getIndex_bayte_arr(sDate.Date, dateVariants, DATE_VARIANTS_COUNT);
		currentSettings[DATE_VARIANTS_INDEX] = index;
		
		index = getIndex_bayte_arr(sTime.Hours, hourVariants, HOUR_VARIANTS_COUNT);
		currentSettings[HOUR_VARIANTS_INDEX] = index;
		
		index = getIndex_bayte_arr(sTime.Minutes, minuteVariants, MINUTE_VARIANTS_COUNT);
		currentSettings[MINUTE_VARIANTS_INDEX] = index;
		
		index = getIndex_bayte_arr(sDate.WeekDay, dayOfWeekVariants, DAY_OF_WEEK_VARIANTS_COUNT);
		currentSettings[DAY_OF_WEEK_VARIANTS_INDEX] = index;

	}
	
}

void Button::fillSocketPowerCurrentSettings()
{
	if (currentSetting == UP_POWER_VARIANTS_INDEX  
		| currentSetting == DOWN_POWER_VARIANTS_INDEX)
		
	{
		uint8_t index;
		
		index = getIndex_word_arr((uint16_t)upSocket.loadPowerKVT * 1000, Powers, POWER_VARIANTS_COUNT);
		currentSettings[UP_POWER_VARIANTS_INDEX] = index;

		index = getIndex_word_arr((uint16_t)downSocket.loadPowerKVT * 1000, Powers, POWER_VARIANTS_COUNT);
		currentSettings[DOWN_POWER_VARIANTS_INDEX] = index;

	}
}

void Button::processPowerChange()
{
	if (currentSetting == UP_POWER_VARIANTS_INDEX  
		| currentSetting == DOWN_POWER_VARIANTS_INDEX)
		
	{
		switch (currentSetting)
		{
		case UP_POWER_VARIANTS_INDEX:
			{
				upSocket.loadPowerKVT  = (float)Powers[currentSettings[currentSetting]] / 1000;
				break;
			}
		case DOWN_POWER_VARIANTS_INDEX:
			{
				upSocket.loadPowerKVT  = (float)Powers[currentSettings[currentSetting]] / 1000;
				break;
			}	
		}
	}
}*/
