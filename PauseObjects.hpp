#ifndef __PAUSEOBJECTS__H
#define __PAUSEOBJECTS__H

#include "BeerPause.hpp"
#include <vector>

std::vector<Pause*> pausesVector_1 = { new Pause(0, "45|300", 45, 300),
									new Pause(0, "52|300", 52, 300),
									new Pause(0, "68|300", 68, 300), 
									new Pause(0, "72|300", 72, 300),
									new Pause(0, "79|300", 79, 300) };
Pauses* pauses_45_52_68_72_79 = new Pauses(0, "45_52_68_72_79", MASHING, pausesVector_1);

std::vector<Pause*> pausesVector_2 = {new Pause(0, "62|300", 62, 300),
									new Pause(0, "68|1800", 68, 300), 
									new Pause(0, "72|1800", 72, 300),
									new Pause(0, "81|600", 81, 300) };
Pauses* pauses_62_68_72_81 = new Pauses(1, "62|68|72|81", MASHING, pausesVector_2);

std::vector<Pause*> pausesVector_3 = { 
	new Pause(0, "30|20", 30, 20)
};
Pauses* pauses_30_20c = new Pauses(2, "30-20c", MASHING, pausesVector_3);

std::vector<Pauses*> PausesVector = { pauses_45_52_68_72_79, pauses_62_68_72_81, pauses_30_20c };

#endif