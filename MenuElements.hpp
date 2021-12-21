#ifndef __MENUELEMENTS__H
#define __MENUELEMENTS__H

#include "main.h"
#include "MenuElement.hpp"


bool restorePauses(uint16_t* param);
bool restoreDelayEndTunes(uint16_t* param);
bool restoreDelayBeginTunes(uint16_t* param);
bool setDefaults(uint16_t* param);
bool clearCounters(uint16_t* param);
bool setYear(uint16_t* param);
bool restoreYear(uint16_t* param);
bool setMonth(uint16_t* param);
bool restoreMonth(uint16_t* param);
bool setDate(uint16_t* param);
bool restoreDate(uint16_t* param);
bool setHour(uint16_t* param);
bool restoreHour(uint16_t* param);
bool setMinute(uint16_t* param);
bool restoreMinute(uint16_t* param);
bool setWeekDay(uint16_t* param);
bool restoreWeekDay(uint16_t* param);
bool setUpSocketLoadPower(uint16_t* param);
bool setDownSocketLoadPower(uint16_t* param);
bool setV12SocketLoadPower(uint16_t* param);
void InitMenuElements(MenuElement* lastElement);

void AddMashingPauseDescription(char* text, MenuElementBase* elembase);
void AddBoilingPauseDescription(char* text, MenuElementBase* elembase);
void AddChildTuneValue(char* text, MenuElementBase* elembase);
bool ChangePumpMode(uint16_t* param);

bool startPauses(uint16_t* param);

bool MashingPauseStart(uint16_t* param);
bool BoilingPauseStart(uint16_t* param);

bool DelayBeginOnOff(uint16_t* param);
bool DelayEndOnOff(uint16_t* param);

#endif
