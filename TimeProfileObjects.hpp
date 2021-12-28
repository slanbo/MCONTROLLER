#ifndef __TIMEPROFILEOBJECTS__H
#define __TIMEPROFILEOBJECTS__H

#include "TimeProfile.hpp"

//FIX TEMP PROFILE

//Date Profiles

DatePeriodValue *adpv = new DatePeriodValue(1, "All time", 3, 0, 1, 23, 59, 0, 0, 0, 0, 0, &airFixTemp, &airFixTemp);
std::vector<PeriodValue*> ADPValues = {adpv};
PeriodValuesCollection* airTempDVPC = new PeriodValuesCollection(ADPValues);

DatePeriodValue *bdpv1 = new DatePeriodValue(1, "Night time 1", 0, 0, 1, 6, 59, 0, 0, 0, 0, 0, &batNightFixTemp, &batNightFixTemp);
DatePeriodValue *bdpv2 = new DatePeriodValue(2, "Day time", 0, 7, 0, 22, 59, 0, 0, 0, 0, 0, &batDayFixTemp, &batDayFixTemp);
DatePeriodValue *bdpv3 = new DatePeriodValue(3, "Night time 2", 0, 23, 0, 23, 59, 0, 0, 0, 0, 0, &batNightFixTemp, &batNightFixTemp);
std::vector<PeriodValue*> BDPValues = { bdpv1, bdpv2, bdpv3 };
PeriodValuesCollection* batTempDVPC = new PeriodValuesCollection(BDPValues);

DatePeriodValue *cdpv = new DatePeriodValue(1, "All day", 0, 0, 1, 23, 59, 0, 0, 0, 0, 0, &CODangerLevel, &CODangerLevel);
std::vector<PeriodValue*> CDPValues = { cdpv };
PeriodValuesCollection* CODVPC = new PeriodValuesCollection(CDPValues);

DatePeriodValue *ldpv = new DatePeriodValue(1, "All day", 0, 0, 1, 23, 59, 0, 0, 0, 0, 0, &LightEdge, &LightEdge);
std::vector<PeriodValue*> LDPValues = { ldpv };
PeriodValuesCollection* lightDVPC = new PeriodValuesCollection(LDPValues);


//Time Profiles
TimePeriodValue* mtp_1 = new TimePeriodValue(1, "Пауза 1", &mashingPause1Temp, &mashingPause1Temp, &mashingPause1Time, &mashingPause1Active, &mashingPause1StayOn);
TimePeriodValue* mtp_2 = new TimePeriodValue(2, "Пауза 2", &mashingPause2Temp, &mashingPause2Temp, &mashingPause2Time, &mashingPause2Active, &mashingPause2StayOn);
TimePeriodValue* mtp_3 = new TimePeriodValue(3, "Пауза 3", &mashingPause3Temp, &mashingPause3Temp, &mashingPause3Time, &mashingPause3Active, &mashingPause3StayOn);
TimePeriodValue* mtp_4 = new TimePeriodValue(4, "Пауза 4", &mashingPause4Temp, &mashingPause4Temp, &mashingPause4Time, &mashingPause4Active, &mashingPause4StayOn);
TimePeriodValue* mtp_5 = new TimePeriodValue(5, "Пауза 5", &mashingPause5Temp, &mashingPause5Temp, &mashingPause5Time, &mashingPause5Active, &mashingPause5StayOn);
TimePeriodValue* mtp_6 = new TimePeriodValue(6, "Пауза 6", &mashingPause6Temp, &mashingPause6Temp, &mashingPause6Time, &mashingPause6Active, &mashingPause6StayOn);

std::vector<PeriodValue*> MPValues = {mtp_1, mtp_2, mtp_3, mtp_4, mtp_5, mtp_6};
PeriodValuesCollection* mashingDVPC = new PeriodValuesCollection(MPValues, &mashboilStayOnDelta);

TimePeriodValue* btp_1 = new TimePeriodValue(1, "Варка 1", &boilingPause1Temp, &boilingPause1Temp, &boilingPause1Time, &boilingPause1Active, &boilingPause1StayOn);
TimePeriodValue* btp_2 = new TimePeriodValue(2, "Варка 2", &boilingPause2Temp, &boilingPause2Temp, &boilingPause2Time, &boilingPause2Active, &boilingPause2StayOn);
TimePeriodValue* btp_3 = new TimePeriodValue(3, "Варка 3", &boilingPause3Temp, &boilingPause3Temp, &boilingPause3Time, &boilingPause3Active, &boilingPause3StayOn);

std::vector<PeriodValue*> BPValues = { btp_1, btp_2, btp_3};
PeriodValuesCollection* boilingTempDVPC = new PeriodValuesCollection(BPValues, &mashboilStayOnDelta);

TimePeriodValue* dtp_1 = new TimePeriodValue(1, "Сушка 1", &dryingPause1Temp, &dryingPause1Temp, &dryingPause1Time, &dryingPause1Active, &dryingPause1StayOn);
TimePeriodValue* dtp_2 = new TimePeriodValue(2, "Сушка 2", &dryingPause2Temp, &dryingPause2Temp, &dryingPause2Time, &dryingPause2Active, &dryingPause2StayOn);
TimePeriodValue* dtp_3 = new TimePeriodValue(3, "Сушка 3", &dryingPause3Temp, &dryingPause3Temp, &dryingPause3Time, &dryingPause3Active, &dryingPause3StayOn);

std::vector<PeriodValue*> DPValues = { dtp_1, dtp_2, dtp_3 };
PeriodValuesCollection* dryingTempDVPC = new PeriodValuesCollection(DPValues, &dryingStayOnDelta);





#endif