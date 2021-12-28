#include "BeerPause.hpp"

Pause::Pause(uint16_t ID, const char* name, uint8_t temperature, uint16_t time)
	: BaseObject(ID, name),
	Temperature(temperature),
	Time(time)
{
}

Pauses::Pauses(uint16_t ID,
	const char* name,
	std::vector<Pause*>& pausesVector,
	std::vector<intTune*>& tempTunesVector,
	std::vector<intTune*>& timeTunesVector,
	std::vector<intTune*>& activityTunesVector,
	std::vector<intTune*>& savedStayOnTimeVector
	)
	: BaseObject(ID, name),
	PausesVector(pausesVector),
	TempTunesVector(tempTunesVector),
	TimeTunesVector(timeTunesVector),
	ActivityTunesVector(activityTunesVector),
	SavedStayOnTimeVector(savedStayOnTimeVector)	
{
}

void Pauses::saveToTunes()
{
	uint8_t i = 0;
	for (auto pause : PausesVector)
	{
		TempTunesVector.at(i)->_setVal(pause->Temperature); 
		TempTunesVector.at(i)->save();
			
		TimeTunesVector.at(i)->_setVal(pause->Time); 
		TimeTunesVector.at(i)->save();
			
		ActivityTunesVector.at(i)->_setVal(1); 
		ActivityTunesVector.at(i)->save();
			
		SavedStayOnTimeVector.at(i)->_setVal(0); 
		SavedStayOnTimeVector.at(i)->save();
			
		i++;
	}
		for (uint8_t i = PausesVector.size(); i < TempTunesVector.size(); i++)
		{
			TempTunesVector.at(i)->_setVal(0); 
			TempTunesVector.at(i)->save();
			
			TimeTunesVector.at(i)->_setVal(0); 
			TimeTunesVector.at(i)->save();
			
			ActivityTunesVector.at(i)->_setVal(0); 
			ActivityTunesVector.at(i)->save();
			
			SavedStayOnTimeVector.at(i)->_setVal(0); 
			SavedStayOnTimeVector.at(i)->save();
		}
}