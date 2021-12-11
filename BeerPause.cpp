#include "BeerPause.hpp"

Pause::Pause(uint16_t ID, std::string name, uint8_t temperature, uint16_t time)
	: BaseObject(ID, name),
	Temperature(temperature),
	Time(time)
{
}


Pauses::Pauses(uint16_t ID, std::string name, pausestype type)
	: BaseObject(ID, name),
	Type(type)
{
	
}

void Pauses::saveToTunes()
{
	uint8_t i = 0;
	for (auto pause : pauses)
		if (Type == MASHING)
		{
			mashingTemperatureTunesVector.at(i)->_setVal(pause->Temperature); 
			mashingTemperatureTunesVector.at(i)->save();
			
			mashingTimeTunesVector.at(i)->_setVal(pause->Time); 
			mashingTimeTunesVector.at(i)->save();
			
			mashingActivityTunesVector.at(i)->_setVal(1); 
			mashingActivityTunesVector.at(i)->save();
		}
		else if (Type == BOILING)
		{
			boilingTemperatureTunesVector.at(i)->_setVal(pause->Temperature); 
			boilingTemperatureTunesVector.at(i)->save();
			
			boilingTimeTunesVector.at(i)->_setVal(pause->Time); 
			boilingTimeTunesVector.at(i)->save();
			
			boilingActivityTunesVector.at(i)->_setVal(1); 
			boilingActivityTunesVector.at(i)->save();
			
		}
}


void Pauses::addPause(Pause* pause)
{
	pauses.push_back(pause);
}
