#ifndef __PAUSEOBJECTS__H
#define __PAUSEOBJECTS__H

#include "BeerPause.hpp"
#include <vector>

std::vector<Pause*> pausesVector_1 = { new Pause(0, "45|900", 45, 900), //кислотная
									new Pause(0, "48|600", 48, 600), //белковая амнокислоты
									new Pause(0, "57|600", 57, 600), //белковая другие
									new Pause(0, "62|2000", 62, 2000), //осахаривание бета амлаза
									new Pause(0, "70|1600", 70, 1600), //осахаривание альфа амлаза
									new Pause(0, "79|600", 79, 600)}; //mash out
Pauses* pauses_45_52_68_72_79 = new Pauses(0, "45|48|57|62|70|79", MASHING, pausesVector_1);

std::vector<Pause*> pausesVector_2 = {new Pause(0, "48|600", 48, 600),  //белковая амнокислоты
									new Pause(0, "57|600", 57, 600),  //белковая другие
									new Pause(0, "68|3600", 68, 3600), //осахаривание альфа бета амлаза
									new Pause(0, "79|600", 79, 600) }; //mash out
Pauses* pauses_62_68_72_81 = new Pauses(1, "48|57|68|79", MASHING, pausesVector_2);

std::vector<Pause*> pausesVector_3 = { 
	new Pause(0, "25|180", 25, 180)
};
Pauses* pauses_25 = new Pauses(2, "25-180c", MASHING, pausesVector_3); //test


std::vector<Pause*> boilingPausesVector_1 = { 
									new Pause(0, "98|600", 98, 600),//белковая амнокислоты 
									new Pause(0, "98|3600", 98, 3600), 
									new Pause(0, "98|600", 98, 300)}; 

Pauses* boilingPauses_1 = new Pauses(1, "98|98|98", BOILING, boilingPausesVector_1);

std::vector<Pauses*> PausesVector = { pauses_45_52_68_72_79, pauses_62_68_72_81, pauses_25, boilingPauses_1};


#endif