#ifndef __PCOUNTEROBJECTS__H
#define __PCOUNTEROBJECTS__H

#include "PCounterControl.hpp"
#include "SocketObjectsExt.hpp"
#include "TuneObjectsExt.hpp"

PCounterControl* dayPCounter = new PCounterControl("Счетчик день",
	&dayPCounterOnOffTune,
	&PCounterSockets, 
	&dayPCounterFirstByte,
	&dayPCounterSecondByte,
	7, 
	0, 
	22, 
	59);

PCounterControl* nightPCounter = new PCounterControl("Счетчик ночь",
	&dayPCounterOnOffTune,
	&PCounterSockets, 
	&dayPCounterFirstByte,
	&dayPCounterSecondByte,
	23, 
	0, 
	6, 
	59);

std::vector<PCounterControl*> PCountersVector = { &dayPCounter, &nightPCounter};

#endif