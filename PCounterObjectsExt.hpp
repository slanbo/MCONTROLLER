#ifndef __PCOUNTEROBJECTSEXT__H
#define __PCOUNTEROBJECTSEXT__H

#include "PCounterControl.hpp"
#include "SocketObjectsExt.hpp"
#include "TuneObjectsExt.hpp"

#define PCOUNTERS_SIZE 2	
	
extern PCounterControl* nightPCounter;
extern PCounterControl* dayPCounter;

extern std::vector<PCounterControl*> PCountersVector;

#endif

