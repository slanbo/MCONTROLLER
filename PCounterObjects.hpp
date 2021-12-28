#ifndef __PCOUNTEROBJECTS__H
#define __PCOUNTEROBJECTS__H

#include "PCounterControl.hpp"
#include "SocketObjectsExt.hpp"
#include "TuneObjectsExt.hpp"

PCounterControl* dayPCounter = new PCounterControl(
	"Счетчик день",
	"DAY_PCOUNT",
	&dayPCounterOnOffTune,
	&PCounterSockets, 
	&dayPCounterVal,
	7, 
	0, 
	22, 
	59);

PCounterControl* nightPCounter = new PCounterControl(
	"Счетчик ночь",
	"NIGHT_PCOUNT",
	&nightPCounterOnOffTune,
	&PCounterSockets, 
	&nightPCounterVal,
	23, 
	0, 
	6, 
	59);

std::vector<PCounterControl*> PCountersVector = { dayPCounter, nightPCounter};

#endif