#ifndef __TEMP_PAUSES__H
#define __TEMP_PAUSES__H

#include "TempPause.hpp"
#include "Sensors.hpp"
#include "SocketObjectsExt.hpp"

#define MASHING_PAUSES_SIZE 6
#define BOILING_PAUSES_SIZE 3

extern TempPause MashPause_1;
extern TempPause MashPause_2;
extern TempPause MashPause_3;
extern TempPause MashPause_4;
extern TempPause MashPause_5;
extern TempPause MashPause_6;

extern std ::vector<TempPause*> MashingPausesV;
extern std::vector <TempPause*> BoilingPausesV;
	
#endif