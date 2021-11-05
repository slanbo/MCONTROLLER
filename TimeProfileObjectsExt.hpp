#pragma once
#include "TimeProfile.hpp"

extern void createAllTimeTunedProfile(TimeProfile* tp, intTune* fixLevelTume);
extern void createAirTempTimeProfile(TimeProfile* tp, intTune* timeProfile);
extern void createBatTempTimeProfile(TimeProfile* tp, intTune* timeProfile);
extern void createLightTimeProfile(TimeProfile* tp, intTune* timeProfile);
extern void createDryingTimeProfile(TimeProfile* tp, intTune* timeProfile);
extern void deleteProfile(TimeProfile* tp);