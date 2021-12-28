
#include "MenuElements.hpp"
#include "TuneObjectsExt.hpp"
#include "rtc.h"
#include "SocketObjectsExt.hpp"
#include "IRMotionSensor.hpp"
#include "MenuElement.hpp"
#include "Auxiliary.hpp"
#include "PauseObjectsExt.hpp"
#include "TimeProfileObjectsExt.hpp"
#include "ModeObjectsExt.hpp"
#include "FreeRTOS.h"
#include "MenuClass.hpp"
#include "Bizzer.hpp"
#include "DelayDateObjectsExt.hpp"
#include "PCounterObjectsExt.hpp"

extern Bizzer alarmBizzer;
extern Menu* mainMenu; 
extern SemaphoreHandle_t flashmut_handle;
extern MenuElement mi_125;

extern std::vector < MenuElement *> menuElements;

bool setDefaults(uint16_t* param)
{
	
	clearTunesInFlash();
	setDefaultTuneVals();
	
	return true;
}
;

bool restoreDelayBeginTunes(uint16_t* param)
{

	compareRes res = delayBegin->CompareDelayAndCurrentDate();
	
	if (res == LESS)
	{
		delayBegin->SeveCurrentToDelayDate();
	}
	return true;
}
;

bool restorePauses(uint16_t* param)
{
	PausesVector.at(*param - 1)->saveToTunes();
	mashingDVPC->ResetPeriodes();
	boilingTempDVPC->ResetPeriodes();
	
	
	return true;
}

bool restoreDryingPauses(uint16_t* param)
{
	DryingPausesVector.at(*param - 1)->saveToTunes();
	dryingTempDVPC->ResetPeriodes();
	
	
	return true;
}



bool startPauses(uint16_t* param)
{
	
	switch (*param)
	{
	case 1:
		{
			if (beerModeIndex._getVal() == 0)
			{
				BeerPreparingMode->mashingControl->DPVCollection->ResetPeriodes();
				BeerPreparingMode->mashingControl->setOn(true);
			}
			else
			{
				BeerPreparingMode->boilingControl->DPVCollection->ResetPeriodes();
				BeerPreparingMode->boilingControl->setOn(true);
			}
		break;
		}
	case 2:
		{
			if (beerModeIndex._getVal() == 0)
			{
				BeerPreparingMode->mashingControl->DPVCollection->RestorePeriodsStates(0xff);
				BeerPreparingMode->mashingControl->setOn(true);
			}
			else
			{
				BeerPreparingMode->boilingControl->DPVCollection->RestorePeriodsStates(0xff);
				BeerPreparingMode->boilingControl->setOn(true);
			}
			break;
		}
	case 3:
		{
			if (beerModeIndex._getVal() == 0)
			{
				uint16_t currval = BeerPreparingMode->mashingControl->_get_current_val();
				BeerPreparingMode->mashingControl->DPVCollection->RestorePeriodsStates(currval);
				BeerPreparingMode->mashingControl->setOn(true);
			}
			else
			{
				uint16_t currval = BeerPreparingMode->boilingControl->_get_current_val();
				BeerPreparingMode->boilingControl->DPVCollection->RestorePeriodsStates(currval);
				BeerPreparingMode->boilingControl->setOn(true);
			}
			break;
		}
	default:
		{
			break;
		}
	}
		
	EXIT_SETUP_MODE();

	return true;
}

bool startDryingPauses(uint16_t* param)
{
	
	switch (*param)
	{
	case 1:
		{
			DryingMode->airTempControl->DPVCollection->ResetPeriodes();
			DryingMode->airTempControl->setOn(true);
			break;
		}
	case 2:
		{
			DryingMode->airTempControl->DPVCollection->RestorePeriodsStates(0xff);
			DryingMode->airTempControl->setOn(true);
			break;
		}
	case 3:
		{
			uint16_t currval = DryingMode->airTempControl->_get_current_val();
			DryingMode->airTempControl->DPVCollection->RestorePeriodsStates(currval);
			DryingMode->airTempControl->setOn(true);
			break;
		}
	default:
		{
			break;
		}
	}
		
	EXIT_SETUP_MODE();

	return true;
}


bool restoreDelayEndTunes(uint16_t* param)
{
	compareRes res = delayEnd->CompareDelayAndCurrentDate();
	
	if (res == LESS)
	{
		delayEnd->SeveCurrentToDelayDate();
	}
	return true;
}
;


bool clearCounters(uint16_t* param)
{
	
	dayPCounter->set_VT_Seconds(0);
	dayPCounter->saveToFlash();
	nightPCounter->set_VT_Seconds(0);
	nightPCounter->saveToFlash();

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


bool setYear(uint16_t* param)
{
	RTC_DateTypeDef sDate = { 0 };
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	sDate.Year = *param - 2000;
	HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	return true;
}
;

bool restoreYear(uint16_t* param)
{
	RTC_DateTypeDef sDate = { 0 };
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	*param = sDate.Year + 2000;
	return true;
}
;

bool restoreDelayYear(uint16_t* param)
{
	RTC_DateTypeDef sDate = { 0 };
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	if (*param < sDate.Year + 2000)
	*param = sDate.Year + 2000;
	return true;
}
;

bool setMonth(uint16_t* param)
{
	RTC_DateTypeDef sDate = { 0 };
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	sDate.Month = *param;
	HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	return true;
}
;

bool restoreMonth(uint16_t* param)
{
	RTC_DateTypeDef sDate = { 0 };
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	*param = sDate.Month;
	return true;
}


bool setDate(uint16_t* param)
{
	RTC_DateTypeDef sDate = { 0 };
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	sDate.Date = *param;
	HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	return true;
}
;

bool restoreDate(uint16_t* param)
{
	RTC_DateTypeDef sDate = { 0 };
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	*param = sDate.Date;
	return true;
}
;

bool setHour(uint16_t* param)
{
	RTC_TimeTypeDef sTime = { 0 };
	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	sTime.Hours = *param;
	HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	return true;
}
;

bool restoreHour(uint16_t* param)
{
	RTC_TimeTypeDef sTime = { 0 };
	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	*param = sTime.Hours;
	return true;
}
;

bool setMinute(uint16_t* param)
{
	RTC_TimeTypeDef sTime = { 0 };
	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	sTime.Minutes = *param;
	HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	return true;
}
;

bool restoreMinute(uint16_t* param)
{
	RTC_TimeTypeDef sTime = { 0 };
	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	*param = sTime.Minutes;
	return true;
}
;

bool setWeekDay(uint16_t* param)
{
	RTC_DateTypeDef sDate = { 0 };
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	sDate.WeekDay = *param;
	HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	
	return true;
}
;

bool restoreWeekDay(uint16_t* param)
{
	RTC_DateTypeDef sDate = { 0 };
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	*param = sDate.WeekDay;
	return true;
}
;

bool setUpSocketLoadPower(uint16_t* param)
{
	upSocket->_setLoadPowerVT(*param);
	return true;
}
;

bool setDownSocketLoadPower(uint16_t* param)
{
	downSocket->_setLoadPowerVT(*param);
	return true;
}
;

bool setV12SocketLoadPower(uint16_t* param)
{
	V12_Socket->_setLoadPowerVT(*param);
	return true;
}
;
	
void InitMenuElements(MenuElement* lastElement)
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
		if (currItem->MenuElementTypeIndex == INT_SELECTOR_MENU_ELEMENT_TYPE_INDEX)
			currItem->init();
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
			if (cursor != nullptr & cursor->ParentItem == currItem->ParentItem)
			{
				found = true;
				currItem->PrevItem = cursor;
			}
		}
		if (!found)
		{
			cursor = lastItem;
			while (cursor != nullptr & cursor->ParentItem != currItem->ParentItem)
			{
				cursor = cursor->PrevInListItem;
			}
			if (cursor != nullptr & cursor->ParentItem == currItem->ParentItem)
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
		//if (currItem == &mi_125)
		//{
		//	found = false;
		//}
		
		
		found = false;
		cursor = currItem->NextInListItem;
				
		if (cursor != nullptr)
		{
			while (cursor != nullptr & cursor->ParentItem != currItem->ParentItem)
			{
				cursor = cursor->NextInListItem;
			}
			if (cursor != nullptr & cursor->ParentItem == currItem->ParentItem)
			{
				found = true;
				currItem->NextItem = cursor;
			}
			
		}	
		if (!found)
		{
			cursor = firstItem;
			while (cursor != nullptr & cursor->ParentItem != currItem->ParentItem)
			{
				cursor = cursor->NextInListItem;
			}
			if (cursor != nullptr & cursor->ParentItem == currItem->ParentItem)
			{
				found = true;
				currItem->NextItem = cursor;
			}
		}
		currItem = currItem->NextInListItem;
	}
}
;
	
void AddMashingPauseDescription(char* text, MenuElementBase* elembase)
{
	MenuElement* elem = (MenuElement*)elembase;
	AddIntChars(text, mashingTemperatureTunesVector.at(elem->Parametr - 1)->_getVal(), 2, ' ');
	AddIntChars(text, mashingTimeTunesVector.at(elem->Parametr - 1)->_getVal(), 5, ' ');
}

void AddBoilingPauseDescription(char* text, MenuElementBase* elembase)
{
	MenuElement* elem = (MenuElement*)elembase;
	AddIntChars(text, boilingTemperatureTunesVector.at(elem->Parametr - 1)->_getVal(), 2, ' ');
	AddIntChars(text, boilingTimeTunesVector.at(elem->Parametr - 1)->_getVal(), 5, ' ');
}

void AddDryingPauseDescription(char* text, MenuElementBase* elembase)
{
	MenuElement* elem = (MenuElement*)elembase;
	AddIntChars(text, dryingTemperatureTunesVector.at(elem->Parametr - 1)->_getVal(), 2, ' ');
	AddIntChars(text, dryingTimeTunesVector.at(elem->Parametr - 1)->_getVal(), 5, ' ');
}

void AddChildTuneValue(char* text, MenuElementBase* elembase)
{
	MenuElement* elemchilde = (MenuElement*)elembase->ChildItem;
	AddIntChars(text, elemchilde->Tune->_getVal(), 4, ' ');
}

bool ChangePumpMode(uint16_t* param)
{
	if (*param != 5)
	{
		PumpOnOffTune._setVal(1);
		PumpOnOffTune.save();
		PumpMode._setVal(*param);
		PumpMode.save();
	}
	else
	{
		PumpOnOffTune._setVal(0);
		PumpOnOffTune.save();
	}
	return true;
}
;

bool ChangeVentMode(uint16_t* param)
{
	if (*param != 5)
	{
		dryingVentOnOffTune._setVal(1);
		dryingVentOnOffTune.save();
		dryingVentMode._setVal(*param);
		dryingVentMode.save();
	}
	else
	{
		dryingVentOnOffTune._setVal(0);
		dryingVentOnOffTune.save();
	}
	return true;
}
;

bool MashingPauseStart(uint16_t* param)
{
	BeerPreparingMode->mashingControl->DPVCollection->SetBeforePausesCompleted(*param);
	BeerPreparingMode->mashingControl->setOn(true);
	
	EXIT_SETUP_MODE();
	
	return true;
}
;

bool BoilingPauseStart(uint16_t* param)
{
	BeerPreparingMode->boilingControl->DPVCollection->SetBeforePausesCompleted(*param);
	BeerPreparingMode->boilingControl->setOn(true);

	EXIT_SETUP_MODE();
	
	return true;
}
;

void EXIT_SETUP_MODE()
{
	SETUP_MODE = 0;
	set_DS_From_RTC();
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

bool DryingPauseStart(uint16_t* param)
{
	DryingMode->airTempControl->DPVCollection->SetBeforePausesCompleted(*param);
	DryingMode->airTempControl->setOn(true);

	EXIT_SETUP_MODE();
	
	return true;
}
;

bool DelayBeginOnOff(uint16_t* param)
{
		
	compareRes res = delayBegin->CompareDelayAndCurrentDate();
	
	if (res == MORE)
	{
		delayBeginOnOffTune._setVal(1);
		delayBeginOnOffTune.save();
		return true;
	}
	else
	{
		delayBeginOnOffTune._setVal(0);
		delayBeginOnOffTune.save();
		return false;
	}
}
;

bool DelayEndOnOff(uint16_t* param)
{
		
	compareRes res = delayEnd->CompareDelayAndCurrentDate();
	if (res == MORE)
	{
		delayEndOnOffTune._setVal(1);
		return true;
	}
	else
	{
		delayEndOnOffTune._setVal(0);
		return false;
	}
}
;

//#endif