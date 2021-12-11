#pragma once
#include "BaseObject.hpp"
#include <vector>
#include "Tune.hpp"
#include "TuneObjectsExt.hpp"

enum pausestype
{
	MASHING,
	BOILING
};

class Pause : public BaseObject
{
public:
	
	Pause(uint16_t ID, std::string name, uint8_t temperature, uint16_t time);
	
	uint8_t Temperature = 0;
	uint16_t Time = 0;
	
};

class Pauses : public BaseObject
{
public:
	Pauses(uint16_t ID, std::string name, pausestype type);
	std::vector<Pause*> pauses;
	void saveToTunes();
	
	pausestype Type;
	
protected:
	void addPause(Pause* pause);
	
};
