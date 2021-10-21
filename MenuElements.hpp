#ifndef __MENUELEMENTS__H
#define __MENUELEMENTS__H

#include "main.h"
#include "MenuElement.hpp"


bool setDefaults(uint16_t param);
bool clearCounters(uint16_t param);
bool setYear(uint16_t param);
bool setMonth(uint16_t param);
bool setDate(uint16_t param);
bool setHour(uint16_t param);
bool setMinute(uint16_t param);
bool setWeekDay(uint16_t param);
bool setUpSocketLoadPower(uint16_t param);
bool setDownSocketLoadPower(uint16_t param);
bool setV12SocketLoadPower(uint16_t param);
void postInitStaticMenuElements(MenuElement* lastElement);

#endif
