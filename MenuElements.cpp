
#include "MenuElements.hpp"
#include "TuneObjectsExt.hpp"
#include "rtc.h"
#include "SocketObjectsExt.hpp"
#include "IRMotionSensor.h"
#include "MenuElement.hpp"

#ifdef _MENU_
//extern MenuElement menuElements[MENU_ITEMS_QUANT];

extern std::vector < MenuElement *> menuElements;

bool setDefaults(uint16_t param)
{
	clearTunesInFlash();
	return true;
}
;

bool clearCounters(uint16_t param)
{
	dayPCounterFirstByte._setVal(0);
	dayPCounterFirstByte.save();
	
	dayPCounterSecondByte._setVal(0);
	dayPCounterSecondByte.save();

	nightPCounterFirstByte._setVal(0);
	nightPCounterFirstByte.save();
	
	nightPCounterSecondByte._setVal(0);
	nightPCounterSecondByte.save();
	
	RTC_TimeTypeDef sTime = { 0 };
	RTC_DateTypeDef sDate = { 0 };
	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

	
	PCounterBeginDate._setVal(sDate.Date);
	PCounterBeginDate.save();
	
	PCounterBeginMonth._setVal(sDate.Month) ;
	PCounterBeginMonth.save();
	
	PCounterBeginYear._setVal(sDate.Year);
	PCounterBeginYear.save();
	
	PCounterBeginHour._setVal(sTime.Hours);
	PCounterBeginHour.save();
	
	PCounterBeginMinute._setVal(sTime.Minutes);
	PCounterBeginMinute.save();
	
	return true;
}
;


bool setYear(uint16_t param)
{
	
	RTC_DateTypeDef sDate = { 0 };
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	sDate.Year = param - 2000;
	HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

	return true;
}
;

bool setMonth(uint16_t param)
{
	RTC_DateTypeDef sDate = { 0 };
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	sDate.Month = param;
	HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	
	return true;
}
;

bool setDate(uint16_t param)
{
	RTC_DateTypeDef sDate = { 0 };
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	sDate.Date = param;
	HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	
	return true;
}
;

bool setHour(uint16_t param)
{
	RTC_TimeTypeDef sTime = { 0 };
	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	sTime.Hours = param;
	HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	
	return true;
}
;

bool setMinute(uint16_t param)
{
	RTC_TimeTypeDef sTime = { 0 };
	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	sTime.Minutes = param;
	HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	
	return true;
}
;

bool setWeekDay(uint16_t param)
{
	RTC_DateTypeDef sDate = { 0 };
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	sDate.WeekDay = param;
	HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	
	return true;
}
;

bool setUpSocketLoadPower(uint16_t param)
{
	upSocket._setLoadPowerVT(param);
	return true;
}
;

bool setDownSocketLoadPower(uint16_t param)
{
	downSocket._setLoadPowerVT(param);
	return true;
}
;

bool setV12SocketLoadPower(uint16_t param)
{
	V12_Socket._setLoadPowerVT(param);
	return true;
}
;
	
void postInitStaticMenuElements(MenuElement* lastElement)
{
	
	MenuElementBase* firstItem = nullptr;
	MenuElementBase* lastItem = lastElement;
	MenuElementBase* currItem = lastElement;
	MenuElementBase* cursor = nullptr;
	
	//nextinlist
	while(currItem != nullptr)
	{
		currItem->PrevInListItem->NextInListItem = currItem;
		firstItem = currItem;
		currItem = currItem->PrevInListItem;
	}
	
	
	//childItem
	currItem = firstItem;
	while (currItem != nullptr)
	{
		cursor = currItem->NextInListItem;
		while (cursor != nullptr & cursor->ParentItem != currItem)
		{
			cursor = cursor->NextInListItem;
		}
		currItem->ChildItem = cursor;
		currItem = currItem->NextInListItem;
	}
	
	bool found = false;
	//previtem
	currItem = firstItem;
	while (currItem != nullptr)
	{
		found = false;
		cursor = currItem->PrevInListItem;
		if (cursor != nullptr)
		{
			while (cursor != nullptr & cursor->ParentItem != currItem->ParentItem)
			{
				cursor = cursor->PrevInListItem;
			}
			if (cursor->ParentItem == currItem->ParentItem)
			{
				found = true;
				currItem->PrevItem = cursor;
			}
		}
		if (!found)
		{
			cursor = lastItem;
			while (cursor->ParentItem != currItem->ParentItem)
			{
				cursor = cursor->PrevInListItem;
			}
			if (cursor->ParentItem == currItem->ParentItem)
			{
				found = true;
				currItem->PrevItem = cursor;
			}
		}
		currItem = currItem->NextInListItem;
	}
	
	//next item
	currItem = firstItem;
	while (currItem != nullptr)
	{
		found = false;
		cursor = currItem->NextInListItem;
		if (cursor != nullptr)
		{
			while (cursor != nullptr & cursor->ParentItem != currItem->ParentItem)
			{
				cursor = cursor->NextInListItem;
			}
			if (cursor->ParentItem == currItem->ParentItem)
			{
				found = true;
				currItem->NextItem = cursor;
			}
		}	
		if (!found)
		{
			cursor = firstItem;
			while (cursor->ParentItem != currItem->ParentItem)
			{
				cursor = cursor->NextInListItem;
			}
			if (cursor->ParentItem == currItem->ParentItem)
			{
				found = true;
				currItem->NextItem = cursor;
			}
		}
		currItem = currItem->NextInListItem;
	}
}
;
	
#endif