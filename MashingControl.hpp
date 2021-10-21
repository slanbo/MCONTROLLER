#ifndef __MASHING_CONTROL__H
#define __MASHING_CONTROL__H

#include "Control.hpp"
#include "NTC_10K_B3950.hpp"
#include "TempPause.hpp"
#include "TuneObjectsExt.hpp"
#include "TempPauses.hpp"
#include <string>

class MashingControl : public SensorsSocketsControl
{
public:
	MashingControl
		(
		std::string name,
		intTune* onOffTune,
		std::vector<plugSocket*> &sockets,
		std::vector <TempPause*> &pauses,
		std::vector<NTC_10K_B3950*> &termistors
		);
	
	virtual void FillScreen();
	virtual void ExecuteStep();
	void init();
	void initTempTime(TempPauseTemplate** tempTimes);
	TempPause* getExecutingPause();
	
private:
	
	std::vector <TempPause*> &Pauses;
	uint8_t currentPauseId = 0;
	std::vector<NTC_10K_B3950*> &Termistors;

};
	

#endif