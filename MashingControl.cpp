#include "MashingControl.hpp"

MashingControl::MashingControl
	(
	std::string name,
	intTune* onOffTune,
	std::vector<plugSocket*> &sockets,
	std::vector <TempPause*> &pauses,
	std::vector<NTC_10K_B3950*> &termistors
	)
	: SocketsControl
	(
	name,
	onOffTune,
	sockets
	)
	,
	Pauses(pauses),
	Termistors(termistors)
{
}
;

void MashingControl::ExecuteStep()
{
	
	bool executed;
	
	for (auto p: Pauses)
	{
		executed = p->ExecuteStep();
		if (executed)
		{
			break;
		}
	}
}

void MashingControl::init()
{
	for (auto p : Pauses)
	{
		p->init(Termistors, Sockets);
	}
}

void MashingControl::initTempTime(TempPauseTemplate** tempTimes)
{
	uint8_t count = 0;
	for (auto p: Pauses)
	{
		p->initTempTime(tempTimes[count]);
		count++;
	}
}


TempPause* MashingControl::getExecutingPause()
{
	for (auto p: Pauses)
	{
		PauseState state = p->GetState();
		if (state == HEATING_MAX |
			state == HEATING_MIN |
			state == STAY_ON |
			state == COOLING)
			return p;
	}
	return nullptr;
}


void MashingControl::FillScreen()
{
}
