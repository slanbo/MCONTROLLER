#ifndef __TIMEPROFILEOBJECTS__H
#define __TIMEPROFILEOBJECTS__H

#include "TimeProfile.hpp"

//FIX TEMP PROFILE

TimePeriodValue* mtp_1 = new TimePeriodValue(1, "Пауза 1", &mashingPause1Temp, &mashingPause1Time, &mashingPause1Active, &mashingPause1StayOn);
TimePeriodValue* mtp_2 = new TimePeriodValue(2, "Пауза 2", &mashingPause2Temp, &mashingPause2Time, &mashingPause2Active, &mashingPause2StayOn);
TimePeriodValue* mtp_3 = new TimePeriodValue(3, "Пауза 3", &mashingPause3Temp, &mashingPause3Time, &mashingPause3Active, &mashingPause3StayOn);
TimePeriodValue* mtp_4 = new TimePeriodValue(4, "Пауза 4", &mashingPause4Temp, &mashingPause4Time, &mashingPause4Active, &mashingPause4StayOn);
TimePeriodValue* mtp_5 = new TimePeriodValue(5, "Пауза 5", &mashingPause5Temp, &mashingPause5Time, &mashingPause5Active, &mashingPause5StayOn);
TimePeriodValue* mtp_6 = new TimePeriodValue(6, "Пауза 6", &mashingPause6Temp, &mashingPause6Time, &mashingPause6Active, &mashingPause6StayOn);

PeriodValuesCollection* mashingDVPC = new PeriodValuesCollection(&mashboilStayOnDelta);

TimePeriodValue* btp_1 = new TimePeriodValue(1, "Варка 1", &boilingPause1Temp, &boilingPause1Time, &boilingPause1Active, &boilingPause1StayOn);
TimePeriodValue* btp_2 = new TimePeriodValue(2, "Варка 2", &boilingPause2Temp, &boilingPause2Time, &boilingPause2Active, &boilingPause2StayOn);
TimePeriodValue* btp_3 = new TimePeriodValue(3, "Варка 3", &boilingPause3Temp, &boilingPause3Time, &boilingPause3Active, &boilingPause3StayOn);

PeriodValuesCollection* boilingTempDVPC = new PeriodValuesCollection(&mashboilStayOnDelta);


#endif