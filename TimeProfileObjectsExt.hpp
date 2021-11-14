#pragma once
#include "TimeProfile.hpp"

extern TimeProfile* createAllTimeTunedProfile(intTune* fixLevelTume);
extern TimeProfile* createAirTempTimeProfile(intTune* timeProfile);
extern TimeProfile* createBatTempTimeProfile(intTune* timeProfile);
extern TimeProfile* createCOTimeProfile(intTune* timeProfile);
extern TimeProfile* createLightTimeProfile(intTune* timeProfile);
extern TimeProfile* createDryingTimeProfile(intTune* timeProfile);
extern void deleteProfile(TimeProfile* tp);