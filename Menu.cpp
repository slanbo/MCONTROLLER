#include "Menu.hpp"
#include "Tunes.h"
#include "Lcd_Driver.h"
#include "rtc.h"
#include "IRMotionSensor.h"
#include "Sockets.h"
#include <new>   

menuItem * plugItem;
menuItem * modeItem;
menuItem * dateTimeItem;
menuItem * settingsItem;

bool nullPLUG(uint16_t param)
{
	return true;
};

bool setDefaults(uint16_t param)
{
	clearTunesInFlash();
	return true;
}
;

bool clearCounters(uint16_t param)
{
	dayPCounterFirstByte.val = 0;
	dayPCounterFirstByte.save();
	
	dayPCounterSecondByte.val = 0;
	dayPCounterSecondByte.save();

	nightPCounterFirstByte.val = 0;
	nightPCounterFirstByte.save();
	
	nightPCounterSecondByte.val = 0;
	nightPCounterSecondByte.save();
	
	RTC_TimeTypeDef sTime = { 0 };
	RTC_DateTypeDef sDate = { 0 };
	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

	
	PCounterBeginDate.val = sDate.Date;
	PCounterBeginDate.save();
	
	PCounterBeginMonth.val = sDate.Month;
	PCounterBeginMonth.save();
	
	PCounterBeginYear.val = sDate.Year;
	PCounterBeginYear.save();
	
	PCounterBeginHour.val = sTime.Hours;
	PCounterBeginHour.save();
	
	PCounterBeginMinute.val = sTime.Minutes;
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
	
};

bool setMonth(uint16_t param)
{
	RTC_DateTypeDef sDate = { 0 };
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	sDate.Month = param;
	HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	
	return true;
};

bool setDate(uint16_t param)
{
	RTC_DateTypeDef sDate = { 0 };
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	sDate.Date = param;
	HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	
	return true;
};

bool setHour(uint16_t param)
{
	RTC_TimeTypeDef sTime = { 0 };
	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	sTime.Hours = param;
	HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	
	return true;
};

bool setMinute(uint16_t param)
{
	RTC_TimeTypeDef sTime = { 0 };
	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	sTime.Minutes = param;
	HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	
	return true;
};

bool setWeekDay(uint16_t param)
{
	RTC_DateTypeDef sDate = { 0 };
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	sDate.WeekDay = param;
	HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	
	return true;
};

bool setUpSocketLoadPower(uint16_t param)
{
	upSocket.loadPowerVT = param;
	return true;
}
;

bool setDownSocketLoadPower(uint16_t param)
{
	downSocket.loadPowerVT = param;
	return true;
}
;

bool setV12SocketLoadPower(uint16_t param)
{
	V12_Socket.loadPowerVT = param;
	return true;
}
;

void initMenu()
{
	
char Name[40] = "plug";
plugItem = new menuItem(Name);
	
char modeItemName[40] = "Режим работы";
modeItem = new menuItem(modeItemName);
	
char dateTimeItemName[40] = "Дата время";
dateTimeItem = new menuItem(dateTimeItemName);
	
char settingsName[40] = "Настройки.";
settingsItem = new menuItem(settingsName);

//modes
char habitatModeName[40] = "Контр. среды";
menuItem * habitatModeItem = new menuItem(habitatModeName, 0, &modeIndex);

char beerModeName[40] = "Пригот. пива";
menuItem * beerModeItem = new menuItem(beerModeName, 1, &modeIndex);

char dryingModeName[40] = "Контр. сушки";
menuItem * dryingModeItem = new menuItem(dryingModeName, 2, &modeIndex);

char saunaModeName[40] = "Контр. бани";
menuItem * saunaModeItem = new menuItem(saunaModeName, 3, &modeIndex);


//pump mode
char pumpModeName[40] = "Режим насоса";
menuItem * pumpModeItem = new menuItem(pumpModeName);

char allwaysOnPumpModeName[40] = "Всегда вкл.";
menuItem * allwaysOnPumpModeItem = new menuItem(allwaysOnPumpModeName, 0, &PumpMode);

char allwaysOffPumpModeName[40] = "Всегда выкл.";
menuItem * allwaysOffPumpModeItem = new menuItem(allwaysOffPumpModeName, 1,&PumpMode);

char onIfHeatingPumpModeName[40] = "Вкл. при нагр.";
menuItem * onIfHeatingPumpModeItem = new menuItem(onIfHeatingPumpModeName, 2, &PumpMode);

char pausesPumpModeName[40] = "Вкл. паузами";
menuItem * pausesPumpModeItem = new menuItem(onIfHeatingPumpModeName, 3, &PumpMode);

char SwitchedOnPumpValName[40] = "Время вкл.(сек.)";
menuItem * SwitchedOnPumpValItem = new menuItem(SwitchedOnPumpValName, 1, 0, 1800, 5, &SwitchedOnPumpTime);

char SwitchedOffPumpValName[40] = "Время выкл.(сек.)";
menuItem * SwitchedOffPumpValItem = new menuItem(SwitchedOffPumpValName, 1, 0, 1800, 5, &SwitchedOffPumpTime);


//mashing

char mashingModeName[40] = "Температ. паузы";
menuItem * mashingModeItem = new menuItem(mashingModeName, 0, &beerModeIndex);
	
//mashing Pause 1
char mashingPause1Name[40] = "Пауза 1";
menuItem * mashingPause1Item = new menuItem(mashingPause1Name);

char mashingPause1TempName[40] = "П1 темп.";
menuItem * mashingPause1TempItem = new menuItem(mashingPause1TempName);

char mashingPause1TempValName[40] = "П1 температ.";
menuItem * mashingPause1TempValItem = new menuItem(mashingPause1TempValName, 1, 0, 100, 5, &mashingPause1Temp);

char mashingPause1TimeName[40] = "П1 время";
menuItem * mashingPause1TimeItem = new menuItem(mashingPause1TimeName);

char mashingPause1TimeValName[40] = "П1 время";
menuItem * mashingPause1TimeValItem = new menuItem(mashingPause1TimeValName, 1, 0, 720, 5, &mashingPause1Time);

//mashing Pause 2

char mashingPause2Name[40] = "Пауза 2";
menuItem * mashingPause2Item = new menuItem(mashingPause2Name);

char mashingPause2TempName[40] = "П2 темп.";
menuItem * mashingPause2TempItem = new menuItem(mashingPause2TempName);

char mashingPause2TempValName[40] = "П2 температ.";
menuItem * mashingPause2TempValItem = new menuItem(mashingPause2TempValName, 1, 0, 100, 5, &mashingPause2Temp);

char mashingPause2TimeName[40] = "П2 время";
menuItem * mashingPause2TimeItem = new menuItem(mashingPause2TimeName);

char mashingPause2TimeValName[40] = "П2 время";
menuItem * mashingPause2TimeValItem = new menuItem(mashingPause2TimeValName, 1, 0, 720, 5, &mashingPause2Time);

//mashing Pause 3

char mashingPause3Name[40] = "Пауза 3";
menuItem * mashingPause3Item = new menuItem(mashingPause3Name);

char mashingPause3TempName[40] = "П3 темп.";
menuItem * mashingPause3TempItem = new menuItem(mashingPause3TempName);

char mashingPause3TempValName[40] = "П3 температ.";
menuItem * mashingPause3TempValItem = new menuItem(mashingPause3TempValName, 1, 0, 100, 5, &mashingPause3Temp);

char mashingPause3TimeName[40] = "П3 время";
menuItem * mashingPause3TimeItem = new menuItem(mashingPause3TimeName);

char mashingPause3TimeValName[40] = "П3 время";
menuItem * mashingPause3TimeValItem = new menuItem(mashingPause3TimeValName, 1, 0, 720, 5, &mashingPause3Time);

//mashing Pause 4

char mashingPause4Name[40] = "Пауза 4";
menuItem * mashingPause4Item = new menuItem(mashingPause4Name);

char mashingPause4TempName[40] = "П4 темп.";
menuItem * mashingPause4TempItem = new menuItem(mashingPause4TempName);

char mashingPause4TempValName[40] = "П4 температ.";
menuItem * mashingPause4TempValItem = new menuItem(mashingPause4TempValName, 1, 0, 100, 5, &mashingPause4Temp);

char mashingPause4TimeName[40] = "П4 время";
menuItem * mashingPause4TimeItem = new menuItem(mashingPause4TimeName);

char mashingPause4TimeValName[40] = "П4 время";
menuItem * mashingPause4TimeValItem = new menuItem(mashingPause4TimeValName, 1, 0, 720, 5, &mashingPause4Time);

//mashing Pause 5

char mashingPause5Name[40] = "Пауза 5";
menuItem * mashingPause5Item = new menuItem(mashingPause5Name);

char mashingPause5TempName[40] = "П5 темп.";
menuItem * mashingPause5TempItem = new menuItem(mashingPause5TempName);

char mashingPause5TempValName[40] = "П5 температ.";
menuItem * mashingPause5TempValItem = new menuItem(mashingPause5TempValName, 1, 0, 100, 5, &mashingPause5Temp);

char mashingPause5TimeName[40] = "П5 время";
menuItem * mashingPause5TimeItem = new menuItem(mashingPause5TimeName);

char mashingPause5TimeValName[40] = "П5 время";
menuItem * mashingPause5TimeValItem = new menuItem(mashingPause5TimeValName, 1, 0, 720, 5, &mashingPause5Time);

//mashing Pause 6

char mashingPause6Name[40] = "Пауза 6";
menuItem * mashingPause6Item = new menuItem(mashingPause6Name);

char mashingPause6TempName[40] = "П6 темп.";
menuItem * mashingPause6TempItem = new menuItem(mashingPause6TempName);

char mashingPause6TempValName[40] = "П6 температ.";
menuItem * mashingPause6TempValItem = new menuItem(mashingPause6TempValName, 1, 0, 100, 5, &mashingPause6Temp);

char mashingPause6TimeName[40] = "П6 время";
menuItem * mashingPause6TimeItem = new menuItem(mashingPause6TimeName);

char mashingPause6TimeValName[40] = "П5 время";
menuItem * mashingPause6TimeValItem = new menuItem(mashingPause6TimeValName, 1, 0, 720, 5, &mashingPause6Time);

//boiling

char boilingModeName[40] = "Варка";
menuItem * boilingModeItem = new menuItem(boilingModeName, 1, &beerModeIndex);

//boiling Pause 1
char boilingPause1Name[40] = "Пауза 1";
menuItem * boilingPause1Item = new menuItem(boilingPause1Name);

char boilingPause1TempName[40] = "П1 темп.";
menuItem * boilingPause1TempItem = new menuItem(boilingPause1TempName);

char boilingPause1TempValName[40] = "П1 температ.";
menuItem * boilingPause1TempValItem = new menuItem(boilingPause1TempValName, 1, 0, 100, 5, &boilingPause1Temp);

char boilingPause1TimeName[40] = "П1 время";
menuItem * boilingPause1TimeItem = new menuItem(boilingPause1TimeName);

char boilingPause1TimeValName[40] = "П1 время";
menuItem * boilingPause1TimeValItem = new menuItem(boilingPause1TimeValName, 1, 0, 720, 5, &boilingPause1Time);

//boiling Pause 2

char boilingPause2Name[40] = "Пауза 2";
menuItem * boilingPause2Item = new menuItem(boilingPause2Name);

char boilingPause2TempName[40] = "П2 темп.";
menuItem * boilingPause2TempItem = new menuItem(boilingPause2TempName);

char boilingPause2TempValName[40] = "П2 температ.";
menuItem * boilingPause2TempValItem = new menuItem(boilingPause2TempValName, 1, 0, 100, 5, &boilingPause2Temp);

char boilingPause2TimeName[40] = "П2 время";
menuItem * boilingPause2TimeItem = new menuItem(boilingPause2TimeName);

char boilingPause2TimeValName[40] = "П2 время";
menuItem * boilingPause2TimeValItem = new menuItem(boilingPause2TimeValName, 1, 0, 720, 5, &boilingPause2Time);

//boiling Pause 3

char boilingPause3Name[40] = "Пауза 3";
menuItem * boilingPause3Item = new menuItem(boilingPause3Name);

char boilingPause3TempName[40] = "П3 темп.";
menuItem * boilingPause3TempItem = new menuItem(boilingPause3TempName);

char boilingPause3TempValName[40] = "П3 температ.";
menuItem * boilingPause3TempValItem = new menuItem(boilingPause3TempValName, 1, 0, 100, 5, &boilingPause3Temp);

char boilingPause3TimeName[40] = "П3 время";
menuItem * boilingPause3TimeItem = new menuItem(boilingPause3TimeName);

char boilingPause3TimeValName[40] = "П3 время";
menuItem * boilingPause3TimeValItem = new menuItem(boilingPause3TimeValName, 1, 0, 720, 5, &boilingPause3Time);


//controls
char airTempControlName[40] = "Температ. возд.";
menuItem * airTempControlItem = new menuItem(airTempControlName);

char batTempControlName[40] = "Температ. бат.";
menuItem * batTempControlItem = new menuItem(batTempControlName);

char coControlName[40] = "Угарный газ";
menuItem * coControlItem = new menuItem(coControlName);

char ltControlName[40] = "Освещенность";
menuItem * lightControlItem = new menuItem(ltControlName);


//air temp control sub menu
char airFixTempProfileName[40] = "Фиксированная t";
menuItem * airFixTempProfileItem = new menuItem(airFixTempProfileName, 3, &airTempProfileIndex);

char airFixTempValName[40] = "Знач. температуры";
menuItem * airFixTempValItem = new menuItem(airFixTempValName, 0, 0, 35, &airFixTemp);
	
char airPresenceTempProfileName[40] = "Присутствие";
menuItem * airPresenceTempProfileItem = new menuItem(airPresenceTempProfileName, 0, &airTempProfileIndex);
	
char airAbsenceTempProfileName[40] = "Отсутствие";
menuItem * airAbsenceTempProfileItem = new menuItem(airAbsenceTempProfileName, 1, &airTempProfileIndex);
	
char airWeekendsTempProfileName[40] = "Выходные вт. пт.";
menuItem * airWeekendsTempProfileItem = new menuItem(airWeekendsTempProfileName, 2, &airTempProfileIndex);


char airTempControlOnOffName[40] = "Вкл./Выкл";
menuItem * airTempControlOnOffItem = new menuItem(airTempControlOnOffName);

char airTempControlOnName[40] = "Включить";
menuItem * airTempControlOnItem = new menuItem(airTempControlOnName, 1, &aitTempControlOnOffTune);

char airTempControlOffName[40] = "Выключить";
menuItem * airTempControlOffItem = new menuItem(airTempControlOffName, 0, &aitTempControlOnOffTune);

char airTempControlOnIfMotionName[40] = "Вкл. по движ.";
menuItem * airTempControlOnIfMotionItem = new menuItem(airTempControlOnIfMotionName, 2, &aitTempControlOnOffTune);

char airTempControlMotionsSearchMinName[40] = "Анализ за мин.";
menuItem * airTempControlMotionsSearchMinItem = new menuItem(airTempControlMotionsSearchMinName, 1, 0, IR_MOTION_BUFFER_SIZE, 60, &airTempOnIfMotionMins);


//bat temp control sub menu
char batNightEndTempProfileName[40] = "Ночь нагр. до 80";
menuItem * batNightEndTempProfileItem = new menuItem(batNightEndTempProfileName, 0, &batTempProfileIndex);

char batFixTempValName[40] = "Знач. фикс. темп.";
menuItem * batFixTempValItem = new menuItem(batFixTempValName, 1, 0, 100, &batFixTemp);

char batTempControlOnOffName[40] = "Вкл./Выкл";
menuItem * batTempControlOnOffItem = new menuItem(batTempControlOnOffName);

char batTempControlOnName[40] = "Включить";
menuItem * batTempControlOnItem = new menuItem(batTempControlOnName, 1, &batTempControlOnOffTune);

char batTempControlOffName[40] = "Выключить";
menuItem * batTempControlOffItem = new menuItem(batTempControlOffName, 0, &batTempControlOnOffTune);



// co control sub menu
char coNullLevelName[40] = "Ноль. уров. CO";
menuItem * coNullLevelItem = new menuItem(coNullLevelName);

char coNullLevelValsName[40] = "Ноль. уров. CO";
menuItem * coNullLevelValsItem = new menuItem(coNullLevelValsName, 300, 300, 1500, 10, &CONullLevel);


//co control on off
char coControlOnOffName[40] = "Вкл./Выкл";
menuItem * coControlOnOffItem = new menuItem(coControlOnOffName);

char coControlOnName[40] = "Включить";
menuItem * coControlOnItem = new menuItem(coControlOnName, 1, &coControlOnOffTune);

char coControlOffName[40] = "Выключить";
menuItem * coControlOffItem = new menuItem(coControlOffName, 0, &coControlOnOffTune);

//light control sub menu
char fixDayNightOffProfileName[40] = "Ночь выключено.";
menuItem * fixDayNightOffProfileItem = new menuItem(fixDayNightOffProfileName, 0, &LightProfileIndex);

char dayOnNightOffFixValName[40] = "Порог выключения";
menuItem * dayOnNightOffFixValItem = new menuItem(dayOnNightOffFixValName, 1, 0, 4065, 5, &LightEdge);


char allTimeLightProfileName[40] = "Всегда включено";
menuItem * allTimeLightProfileItem = new menuItem(allTimeLightProfileName, 1, &LightProfileIndex);

char allTimeFixValName[40] = "Порог выключения";
menuItem * allTimeFixValItem = new menuItem(allTimeFixValName, 1, 0, 4065, 5, &LightEdge);

char LightSwitchOffDelayName[40] = "Задержка выключения";
menuItem * LightSwitchOffDelayItem = new menuItem(LightSwitchOffDelayName);


char LightSwitchOffDelayValsName[40] = "Знач. задерж. сек.";
menuItem * LightSwitchOffDelayValsItem = new menuItem(LightSwitchOffDelayValsName, 1, 0, 3600, 60, &LightSwitchOffDelay);

char lightControlOnOffName[40] = "Вкл./Выкл";
menuItem * lightControlOnOffItem = new menuItem(lightControlOnOffName);

char lightControlOnName[40] = "Включить";
menuItem * lightControlOnItem = new menuItem(lightControlOnName, 1, &lightControlOnOffTune);

char lightControlOffName[40] = "Выключить";
menuItem * lightControlOffItem = new menuItem(lightControlOffName, 0, &lightControlOnOffTune);

char lightControlOnIfMotionName[40] = "Вкл. по движ.";
menuItem * lightControlOnIfMotionItem = new menuItem(lightControlOnIfMotionName, 2, &lightControlOnOffTune);

char lightControlMotionsSearchMinName[40] = "Анализ за мин.";
menuItem * lightControlMotionsSearchMinItem = new menuItem(lightControlMotionsSearchMinName, 2, 0, IR_MOTION_BUFFER_SIZE, &lightOnIfMotionMins);

//setting
char dateSetName[40] = "Дата";
menuItem * dateSetItem = new menuItem(dateSetName);
	
char dateValsSetName[40] = "Знач. даты";
menuItem * dateValsSetItem = new menuItem(dateValsSetName, setDate, 1, 1, 31, &dateTune);


char monthSetName[40] = "Месяц";
menuItem * monthSetItem = new menuItem(monthSetName);
	
char monthValsSetName[40] = "Знач. месяца";
menuItem * monthValsSetItem = new menuItem(monthValsSetName, setMonth, 1, 1, 12, &monthTune);


char yearSetName[40] = "Год";
menuItem * yearSetItem = new menuItem(yearSetName);
	
char yearValsSetName[40] = "Знач. года";
menuItem * yearValsSetItem = new menuItem(yearValsSetName, setYear, 2021, 2021, 2031, &yearTune);

	
char hourSetName[40] = "Час";
menuItem * hourSetItem= new menuItem(hourSetName);
	
char hourValsSetName[40] = "Знач. часа";
menuItem * hourValsSetItem= new menuItem(hourValsSetName, setHour, 0, 0, 24, &hourTune);


char minuteSetName[40] = "Минута";
menuItem * minuteSetItem= new menuItem(minuteSetName);
	
char minuteValsSetName[40] = "Знач. минуты";
menuItem * minuteValsSetItem= new menuItem(minuteValsSetName, setMinute, 1, 1, 60, &minuteTune);


char weekDaySetName[40] = "День недели";
menuItem * weekDaySetItem= new menuItem(weekDaySetName);
	
char weekDayValsSetName[40] = "Знач. дня недели";
menuItem * weekDayValsSetItem= new menuItem(weekDayValsSetName, setWeekDay, 1, 1, 7, &weekDayTune);


//defaults
char restoreDefaultTunesName[40] = "Восст. умолч.";
menuItem * restoreDefaultTunesItem= new menuItem(restoreDefaultTunesName, setDefaults);

char clearKVTCountersName[40] = "Обнулить счетч.";
menuItem * clearKVTCountersItem= new menuItem(clearKVTCountersName, clearCounters);

char socketsName[40] = "Разъемы";
menuItem * socketsItem= new menuItem(socketsName);

char upSocketName[40] = "Верхняя розетка";
menuItem * upSocketItem= new menuItem(upSocketName);

char connectedUpSocketPowerName[40] = "Подключ. мощн.";
menuItem * connectedUpSocketPowerItem= new menuItem(connectedUpSocketPowerName, setUpSocketLoadPower, 1, 0, 9000, 100, &upSocketLoadPower);

char V12SocketName[40] = "Разъем 12 вольт";
menuItem * V12SocketItem= new menuItem(V12SocketName);

char connectedV12SocketPowerName[40] = "Подключ. мощн.";
menuItem * connectedV12PowerItem= new menuItem(connectedV12SocketPowerName, setV12SocketLoadPower, 1, 0, 1000, &v12LoadPower);

char downSocketName[40] = "Нижняя розетка";
menuItem * downSocketItem= new menuItem(downSocketName);

char connectedDownSocketPowerName[40] = "Подключ. мощн.";
menuItem * connectedDownSocketPowerItem= new menuItem(connectedDownSocketPowerName, setDownSocketLoadPower, 1, 0, 9000, 100, &downSocketLoadPower);


char midSocketName[40] = "Средняя розетка";
menuItem *  midSocketItem= new menuItem(midSocketName);

char connectedMidSocketPowerName[40] = "Подключ. мощн.";
menuItem *  connectedMidSocketPowerItem= new menuItem(connectedMidSocketPowerName, setDownSocketLoadPower, 1, 0, 9000, 100, &downSocketLoadPower);

	//root menu
	modeItem->init(plugItem, habitatModeItem, settingsItem, dateTimeItem);
	dateTimeItem->init(plugItem, dateSetItem, modeItem, settingsItem);
	settingsItem->init(plugItem, restoreDefaultTunesItem, dateTimeItem, modeItem);
	
	//modes
    habitatModeItem->init(modeItem, airTempControlItem, saunaModeItem, beerModeItem);
	beerModeItem->init(modeItem, mashingModeItem, habitatModeItem, dryingModeItem);
	dryingModeItem->init(modeItem, plugItem, beerModeItem, saunaModeItem);
	saunaModeItem->init(modeItem, plugItem, dryingModeItem, habitatModeItem);

	//controls
	airTempControlItem->init(habitatModeItem, airFixTempProfileItem, coControlItem, batTempControlItem);
	batTempControlItem->init(habitatModeItem, batNightEndTempProfileItem, airTempControlItem, coControlItem);
	coControlItem->init(habitatModeItem, coNullLevelItem, batTempControlItem, lightControlItem);
	lightControlItem->init(habitatModeItem, fixDayNightOffProfileItem, coControlItem, airTempControlItem);
	
	//air temp control sub menu
	airFixTempProfileItem->init(airTempControlItem, airFixTempValItem, airTempControlOnOffItem, airPresenceTempProfileItem);
	airFixTempValItem->init(airFixTempProfileItem, plugItem, plugItem, plugItem);
	
	airPresenceTempProfileItem->init(airTempControlItem, plugItem, airFixTempProfileItem, airAbsenceTempProfileItem);
	airAbsenceTempProfileItem->init(airTempControlItem, plugItem, airPresenceTempProfileItem, airWeekendsTempProfileItem);
	airWeekendsTempProfileItem->init(airTempControlItem, plugItem, airAbsenceTempProfileItem, airTempControlOnOffItem);
	airTempControlOnOffItem->init(airTempControlItem, airTempControlOffItem, airWeekendsTempProfileItem, airFixTempProfileItem);
	
	airTempControlOnItem->init(airTempControlOnOffItem, plugItem, airTempControlOnIfMotionItem, airTempControlOffItem);
	airTempControlOffItem->init(airTempControlOnOffItem, plugItem, airTempControlOnItem, airTempControlOnIfMotionItem);
	airTempControlOnIfMotionItem->init(airTempControlOnOffItem, airTempControlMotionsSearchMinItem, airTempControlOffItem, airTempControlOnItem);
	airTempControlMotionsSearchMinItem->init(airTempControlOnIfMotionItem, plugItem, plugItem, plugItem);
	
	//bat temp control sub menu
	
	batNightEndTempProfileItem->init(batTempControlItem, plugItem, batTempControlOnOffItem, batTempControlOnOffItem);
	batFixTempValItem->init(batNightEndTempProfileItem, plugItem, plugItem, plugItem);
	
	batTempControlOnOffItem->init(batTempControlItem, batTempControlOffItem, batNightEndTempProfileItem, batNightEndTempProfileItem);
	batTempControlOnItem->init(batTempControlOnOffItem, plugItem, batTempControlOffItem, batTempControlOffItem);
	batTempControlOffItem->init(batTempControlOnOffItem, plugItem, batTempControlOnItem, batTempControlOnItem);
	
	//co control sub menu
	coNullLevelItem->init(coControlItem, coNullLevelValsItem, coControlOnOffItem, coControlOnOffItem);
	
	coNullLevelValsItem->init(coNullLevelItem, plugItem, plugItem, plugItem);
	
	coControlOnOffItem->init(coControlItem, coControlOffItem, coNullLevelItem, coNullLevelItem);
	coControlOnItem->init(coControlOnOffItem, plugItem, coControlOffItem, coControlOffItem);
	coControlOffItem->init(coControlOnOffItem, plugItem, coControlOnItem, coControlOnItem);
	
	//light control sub menu
	fixDayNightOffProfileItem->init(lightControlItem, dayOnNightOffFixValItem, lightControlOnOffItem, allTimeLightProfileItem);
	dayOnNightOffFixValItem->init(fixDayNightOffProfileItem, plugItem, plugItem, plugItem);
	
	allTimeLightProfileItem->init(lightControlItem, allTimeFixValItem, fixDayNightOffProfileItem, LightSwitchOffDelayItem);
	allTimeFixValItem->init(allTimeLightProfileItem, plugItem, plugItem, plugItem);
	
	LightSwitchOffDelayItem->init(lightControlItem, LightSwitchOffDelayValsItem, allTimeLightProfileItem, lightControlOnOffItem);
	LightSwitchOffDelayValsItem->init(LightSwitchOffDelayItem, plugItem, plugItem, plugItem); 
	
	lightControlOnOffItem->init(lightControlItem, lightControlOffItem, allTimeLightProfileItem, fixDayNightOffProfileItem);
	
	lightControlOnItem->init(lightControlOnOffItem, plugItem, lightControlOnIfMotionItem, lightControlOffItem);
	lightControlOffItem->init(lightControlOnOffItem, plugItem, lightControlOnItem, lightControlOnIfMotionItem);
	lightControlOnIfMotionItem->init(lightControlOnOffItem, lightControlMotionsSearchMinItem, lightControlOffItem, lightControlOnItem);
	lightControlMotionsSearchMinItem->init(lightControlOnIfMotionItem, plugItem, plugItem, plugItem);

	
	//setting sub menu
	dateSetItem->init(dateTimeItem, dateValsSetItem, weekDaySetItem, monthSetItem);
	monthSetItem->init(dateTimeItem, monthValsSetItem, dateSetItem, yearSetItem);
	yearSetItem->init(dateTimeItem, yearValsSetItem, monthSetItem, hourSetItem);
	hourSetItem->init(dateTimeItem, hourValsSetItem, yearSetItem, minuteSetItem);
	minuteSetItem->init(dateTimeItem, minuteValsSetItem, hourSetItem, weekDaySetItem);
	weekDaySetItem->init(dateTimeItem, weekDayValsSetItem, minuteSetItem, dateSetItem);
	
	dateValsSetItem->init(dateSetItem, plugItem, plugItem, plugItem);
	monthValsSetItem->init(monthSetItem, plugItem, plugItem, plugItem);
	yearValsSetItem->init(yearSetItem, plugItem, plugItem, plugItem);
	hourValsSetItem->init(hourSetItem, plugItem, plugItem, plugItem);
	minuteValsSetItem->init(minuteSetItem, plugItem, plugItem, plugItem);
	weekDayValsSetItem->init(weekDaySetItem, plugItem, plugItem, plugItem);
	
	//defaults sub menu
    restoreDefaultTunesItem->init(settingsItem, plugItem, socketsItem, clearKVTCountersItem);
	clearKVTCountersItem->init(settingsItem, plugItem, restoreDefaultTunesItem, socketsItem);
	socketsItem->init(settingsItem, upSocketItem, clearKVTCountersItem, restoreDefaultTunesItem);
	
	//sockets
	upSocketItem->init(socketsItem, connectedUpSocketPowerItem, V12SocketItem, downSocketItem);
	connectedUpSocketPowerItem->init(upSocketItem, plugItem, plugItem, plugItem);
	
	downSocketItem->init(socketsItem, connectedDownSocketPowerItem, upSocketItem, V12SocketItem);
	connectedDownSocketPowerItem->init(downSocketItem, plugItem, plugItem, plugItem);
	
	V12SocketItem->init(socketsItem, connectedV12PowerItem, downSocketItem, upSocketItem);
	connectedV12PowerItem->init(V12SocketItem, plugItem, plugItem, plugItem);
	
	//mashing
	mashingModeItem->init(beerModeItem, mashingPause1Item, boilingModeItem, boilingModeItem);
	
	//mashing Pause 1
	mashingPause1Item->init(mashingModeItem, mashingPause1TempItem, mashingPause6Item, mashingPause2Item);
	
	//mashing Pause 1 temp
	mashingPause1TempItem->init(mashingPause1Item, mashingPause1TempValItem, mashingPause1TimeItem, mashingPause1TimeItem);
	mashingPause1TempValItem->init(mashingPause1TempItem, plugItem, plugItem, plugItem);
	
	//mashing Pause 1 time
	mashingPause1TimeItem->init(mashingPause1Item, mashingPause1TimeValItem, mashingPause1TempItem, mashingPause1TempItem);
	mashingPause1TimeValItem->init(mashingPause1TimeItem, plugItem, plugItem, plugItem);

	//mashing Pause 2
	mashingPause2Item->init(mashingModeItem, mashingPause2TempItem, mashingPause1Item, mashingPause3Item);
	
	//mashing Pause 2 temp
	mashingPause2TempItem->init(mashingPause2Item, mashingPause2TempValItem, mashingPause2TimeItem, mashingPause2TimeItem);
	mashingPause2TempValItem->init(mashingPause2TempItem, plugItem, plugItem, plugItem);
	
	//mashing Pause 2 time
	mashingPause2TimeItem->init(mashingPause2Item, mashingPause2TimeValItem, mashingPause2TempItem, mashingPause2TempItem);
	mashingPause2TimeValItem->init(mashingPause2TimeItem, plugItem, plugItem, plugItem);

	//mashing Pause 3
	mashingPause3Item->init(mashingModeItem, mashingPause3TempItem, mashingPause2Item, mashingPause4Item);
	
	//mashing Pause 3 temp
	mashingPause3TempItem->init(mashingPause3Item, mashingPause3TempValItem, mashingPause3TimeItem, mashingPause3TimeItem);
	mashingPause3TempValItem->init(mashingPause3TempItem, plugItem, plugItem, plugItem);
	
	//mashing Pause 3 time
	mashingPause3TimeItem->init(mashingPause3Item, mashingPause3TimeValItem, mashingPause3TempItem, mashingPause3TempItem);
	mashingPause3TimeValItem->init(mashingPause3TimeItem, plugItem, plugItem, plugItem);

	//mashing Pause 4
	mashingPause4Item->init(mashingModeItem, mashingPause4TempItem, mashingPause3Item, mashingPause5Item);
	
	//mashing Pause 4 temp
	mashingPause4TempItem->init(mashingPause4Item, mashingPause4TempValItem, mashingPause4TimeItem, mashingPause4TimeItem);
	mashingPause4TempValItem->init(mashingPause4TempItem, plugItem, plugItem, plugItem);
	
	//mashing Pause 4 time
	mashingPause4TimeItem->init(mashingPause4Item, mashingPause4TimeValItem, mashingPause4TempItem, mashingPause4TempItem);
	mashingPause4TimeValItem->init(mashingPause4TimeItem, plugItem, plugItem, plugItem);
	
	//mashing Pause 5
	mashingPause5Item->init(mashingModeItem, mashingPause5TempItem, mashingPause4Item, mashingPause6Item);
	
	//mashing Pause 5 temp
	mashingPause5TempItem->init(mashingPause5Item, mashingPause5TempValItem, mashingPause5TimeItem, mashingPause5TimeItem);
	mashingPause5TempValItem->init(mashingPause5TempItem, plugItem, plugItem, plugItem);
	
	//mashing Pause 5 time
	mashingPause5TimeItem->init(mashingPause5Item, mashingPause5TimeValItem, mashingPause5TempItem, mashingPause5TempItem);
	mashingPause5TimeValItem->init(mashingPause5TimeItem, plugItem, plugItem, plugItem);
	
	//mashing Pause 6
	mashingPause6Item->init(mashingModeItem, mashingPause6TempItem, mashingPause5Item, mashingPause1Item);
	
	//mashing Pause 6 temp
	mashingPause6TempItem->init(mashingPause6Item, mashingPause6TempValItem, mashingPause6TimeItem, mashingPause6TimeItem);
	mashingPause6TempValItem->init(mashingPause6TempItem, plugItem, plugItem, plugItem);
	
	//mashing Pause 6 time
	mashingPause6TimeItem->init(mashingPause6Item, mashingPause6TimeValItem, mashingPause6TempItem, mashingPause6TempItem);
	mashingPause6TimeValItem->init(mashingPause6TimeItem, plugItem, plugItem, plugItem);
	
	
	//boiling
	boilingModeItem->init(beerModeItem, boilingPause1Item, mashingModeItem, mashingModeItem);
	
	//boiling Pause 1
	boilingPause1Item->init(boilingModeItem, boilingPause1TempItem, boilingPause3Item, boilingPause2Item);
	
	//boiling Pause 1 temp
	boilingPause1TempItem->init(boilingPause1Item, boilingPause1TempValItem, boilingPause1TimeItem, boilingPause1TimeItem);
	boilingPause1TempValItem->init(boilingPause1TempItem, plugItem, plugItem, plugItem);
	
	//boiling Pause 1 time
	boilingPause1TimeItem->init(boilingPause1Item, boilingPause1TimeValItem, boilingPause1TempItem, boilingPause1TempItem);
	boilingPause1TimeValItem->init(boilingPause1TimeItem, plugItem, plugItem, plugItem);

	//boiling Pause 2
	boilingPause2Item->init(boilingModeItem, boilingPause2TempItem, boilingPause1Item, boilingPause3Item);
	
	//boiling Pause 2 temp
	boilingPause2TempItem->init(boilingPause2Item, boilingPause2TempValItem, boilingPause2TimeItem, boilingPause2TimeItem);
	boilingPause2TempValItem->init(boilingPause2TempItem, plugItem, plugItem, plugItem);
	
	//boiling Pause 2 time
	boilingPause2TimeItem->init(boilingPause2Item, boilingPause2TimeValItem, boilingPause2TempItem, boilingPause2TempItem);
	boilingPause2TimeValItem->init(boilingPause2TimeItem, plugItem, plugItem, plugItem);

	//boiling Pause 3
	boilingPause3Item->init(boilingModeItem, boilingPause3TempItem, boilingPause2Item, boilingPause1Item);
	
	//boiling Pause 3 temp
	boilingPause3TempItem->init(boilingPause3Item, boilingPause3TempValItem, boilingPause3TimeItem, boilingPause3TimeItem);
	boilingPause3TempValItem->init(boilingPause3TempItem, plugItem, plugItem, plugItem);
	
	//boiling Pause 3 time
	boilingPause3TimeItem->init(boilingPause3Item, boilingPause3TimeValItem, boilingPause3TempItem, boilingPause3TempItem);
	boilingPause3TimeValItem->init(boilingPause3TimeItem, plugItem, plugItem, plugItem);

}