#ifndef __TEMP_PROFILES__H
#define __TEMP_PROFILES__H

#include "TimeProfile.hpp"
	
#define AIR_TEMP_PROFILES_COUNT 4	
#define BAT_TEMP_PROFILES_COUNT 1
#define LIGHT_ADGE_PROFILES_COUNT 2
#define DRYING_TEMP_PROFILES_COUNT 2

	
	extern TimeProfile* airTProfiles[AIR_TEMP_PROFILES_COUNT];	
	extern TimeProfile* batTProfiles[BAT_TEMP_PROFILES_COUNT];	
	extern TimeProfile* lightEdgeProfiles[LIGHT_ADGE_PROFILES_COUNT];
	extern TimeProfile* dryingTempProfiles[DRYING_TEMP_PROFILES_COUNT];
	extern std::vector< TimeProfile *> dryingTempProfilesV;


#endif 	