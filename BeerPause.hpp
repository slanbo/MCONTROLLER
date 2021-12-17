#pragma once
#include "BaseObject.hpp"
#include <vector>
#include "Tune.hpp"
#include "TuneObjectsExt.hpp"

#define MAX_MASHING_PAUSES_QUANT 6
#define MAX_BOILING_PAUSES_QUANT 3


enum pausestype
{
	MASHING,
	BOILING
};

class Pause : public BaseObject
{
public:
	
	Pause(uint16_t ID, const char* name, uint8_t temperature, uint16_t time);
	
	uint8_t Temperature = 0;
	uint16_t Time = 0;
	
};

class Pauses : public BaseObject
{
public:
	Pauses(uint16_t ID, const char* name, pausestype type, std::vector<Pause*>& pausesVector);
	std::vector<Pause*>& PausesVector;
	void saveToTunes();
	
	pausestype Type;
	
protected:
	void addPause(Pause* pause);
	
};
