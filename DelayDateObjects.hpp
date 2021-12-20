#ifndef __DELAYDATEOBJECTS__H
#define __DELAYDATEOBJECTS__H

#include "DelayDateControl.hpp"
#include "TuneObjectsExt.hpp"

DelayDateControl* delayBegin = new DelayDateControl(1,
	"Отлож. старт",
	&delayBeginOnOffTune,
	&delayBeginYear,
	&delayBeginMonth,
	&delayBeginDate,
	&delayBeginHour,
	&delayBeginMinute,
	true);

DelayDateControl* delayEnd = new DelayDateControl(1,
	"Отлож. стоп",
	&delayEndOnOffTune,
	&delayEndYear,
	&delayEndMonth,
	&delayEndDate,
	&delayEndHour,
	&delayEndMinute,
	false);

std::vector<DelayDateControl*> DelayDateVector = { delayBegin, delayEnd };


#endif
