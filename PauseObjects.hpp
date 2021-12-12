#pragma once
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