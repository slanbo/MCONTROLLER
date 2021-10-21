#ifndef __PCOUNTERS__H
#define __PCOUNTERS__H

#include "PCounterControl.hpp"
#include "SocketObjectsExt.hpp"
#include "TuneObjectsExt.hpp"

#define PCOUNTERS_SIZE 2	
	
extern PCounterControl nightPCounter;
extern PCounterControl dayPCounter;

	void initCounters();	
	

#endif
