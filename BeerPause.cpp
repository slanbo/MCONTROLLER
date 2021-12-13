#include "BeerPause.hpp"

Pause::Pause(uint16_t ID, std::string name, uint8_t temperature, uint16_t time)
	: BaseObject(ID, name),
	Temperature(temperature),
	Time(time)
{
}


Pauses::Pauses(uint16_t ID, std::string name, pausestype type, std::vector<Pause*>& pausesVector)
	: BaseObject(ID, name),
	Type(type),
	PausesVector(pausesVector)
{
	
}

void Pauses::saveToTunes()
{
	uint8_t i = 0;
	for (auto pause : PausesVector)
	{
		if (Type == MASHING)
		{
			mashingTemperatureTunesVector.at(i)->_setVal(pause->Temperature); 
			mashingTemperatureTunesVector.at(i)->save();
			
			mashingTimeTunesVector.at(i)->_setVal(pause->Time); 
			mashingTimeTunesVector.at(i)->save();
			
			mashingActivityTunesVector.at(i)->_setVal(1); 
			mashingActivityTunesVector.at(i)->save();
			
			mashingStayOnTunesVector.at(i)->_setVal(0); 
			mashingStayOnTunesVector.at(i)->save();
			
			MashingOnOffTune._setVal(1);
			MashingOnOffTune.save();
		}
		else if (Type == BOILING)
		{
			boilingTemperatureTunesVector.at(i)->_setVal(pause->Temperature); 
			boilingTemperatureTunesVector.at(i)->save();
			
			boilingTimeTunesVector.at(i)->_setVal(pause->Time); 
			boilingTimeTunesVector.at(i)->save();
			
			boilingActivityTunesVector.at(i)->_setVal(1); 
			boilingActivityTunesVector.at(i)->save();
			
			boilingStayOnTunesVector.at(i)->_setVal(0); 
			boilingStayOnTunesVector.at(i)->save();
			
			BoilingOnOffTune._setVal(1);
			BoilingOnOffTune.save();
			
		}
		i++;
	}
	
	if (Type == MASHING)
	{
		for (uint8_t i = PausesVector.size(); i < mashingTemperatureTunesVector.size(); i++)
		{
			mashingTemperatureTunesVector.at(i)->_setVal(0); 
			mashingTemperatureTunesVector.at(i)->save();
			
			mashingTimeTunesVector.at(i)->_setVal(0); 
			mashingTimeTunesVector.at(i)->save();
			
			mashingActivityTunesVector.at(i)->_setVal(0); 
			mashingActivityTunesVector.at(i)->save();
			
			mashingStayOnTunesVector.at(i)->_setVal(0); 
			mashingStayOnTunesVector.at(i)->save();
		}
			
	}
	else if (Type == BOILING)
	{
		for (uint8_t i = PausesVector.size(); i < boilingTemperatureTunesVector.size(); i++)
		{
			boilingTemperatureTunesVector.at(i)->_setVal(0); 
			boilingTemperatureTunesVector.at(i)->save();
			
			boilingTimeTunesVector.at(i)->_setVal(0); 
			boilingTimeTunesVector.at(i)->save();
			
			boilingActivityTunesVector.at(i)->_setVal(0); 
			boilingActivityTunesVector.at(i)->save();
			
			boilingStayOnTunesVector.at(i)->_setVal(0); 
			boilingStayOnTunesVector.at(i)->save();
		}
	}
	
}


void Pauses::addPause(Pause* pause)
{
	PausesVector.push_back(pause);
}
