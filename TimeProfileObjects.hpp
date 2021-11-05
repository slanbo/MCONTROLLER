#ifndef __TIMEPROFILEOBJECTS__H
#define __TIMEPROFILEOBJECTS__H

#include "TimeProfile.hpp"

//FIX TEMP PROFILE


void createAllTimeTunedProfile(TimeProfile* tp, intTune* fixLevelTume)
{
	TimePeriod* all_time_tuned_T = new TimePeriod(0, 1, 23, 59, fixLevelTume);
	
	std::vector<TimePeriod*> all_time_tuned_TPeriods = { all_time_tuned_T };

	DayProfile* all_time_tuned_DayTProfile = new DayProfile(all_time_tuned_TPeriods);
	std::vector<DayProfile*> all_time_tuned_DaysTProfiles = {
		all_time_tuned_DayTProfile,
		all_time_tuned_DayTProfile,
		all_time_tuned_DayTProfile,
		all_time_tuned_DayTProfile,
		all_time_tuned_DayTProfile,
		all_time_tuned_DayTProfile,
		all_time_tuned_DayTProfile
	};

	WeekProfile* all_time_tuned_WeekTProfile = new WeekProfile(all_time_tuned_DaysTProfiles);

	tp = new TimeProfile("ALL TIME TUNED", all_time_tuned_WeekTProfile);
	
}

void createAirTempTimeProfile(TimeProfile* tp, intTune* timeProfile)
{

	switch (timeProfile->_getVal())
	{
	case 1:
		{
			createAllTimeTunedProfile(tp, &airFixTemp);
			break;
		}
	default:
		{
				break;
		}
	}
}

void createBatTempTimeProfile(TimeProfile* tp, intTune* timeProfile)
{

	switch (timeProfile->_getVal())
	{
	case 1:
		{
			createAllTimeTunedProfile(tp, &airFixTemp);
			break;
		}
	default:
		{
			break;
		}
	}
}


void createLightTimeProfile(TimeProfile* tp, intTune* timeProfile)
{

	switch (timeProfile->_getVal())
	{
	case 1:
		{
			createAllTimeTunedProfile(tp, &LightEdge);
			break;
		}
	default:
		{
			break;
		}
	}
}


void createDryingTimeProfile(TimeProfile* tp, intTune* timeProfile)
{

	switch (timeProfile->_getVal())
	{
	case 1:
		{
			createAllTimeTunedProfile(tp, &dryingFixTemp);
			break;
		}
	default:
		{
			break;
		}
	}
}

void deleteProfile(TimeProfile* tp)
{
	delete tp;
}

	/*
	//PRESENCE AIR TEMP PROFILE
	TimePeriod presenceNight_Mon_AirT(0, 1, 6, 59, 18);
	TimePeriod presenceDayAirT(7, 0, 23, 0, 21);
	TimePeriod presenceNight_Evn_AirT(23, 1, 23, 59, 18);
	TimePeriod presenceAirTPeriods[3] = { presenceNight_Mon_AirT, presenceDayAirT, presenceNight_Evn_AirT };

	DayProfile presenceDayAirTProfile(presenceAirTPeriods, 3);
	DayProfile presenceDaysAirTProfiles[7] = { presenceDayAirTProfile, presenceDayAirTProfile, presenceDayAirTProfile, presenceDayAirTProfile, presenceDayAirTProfile, presenceDayAirTProfile, presenceDayAirTProfile };
	WeekProfile presenceWeekAirTProfile(presenceDaysAirTProfiles, 7);
	TimeProfile presenceAirTProfile("PRESENCE", &presenceWeekAirTProfile);

	//ABSENCE

	TimePeriod absenceAirT(0, 1, 23, 59, 2);
	TimePeriod absenceAirTPeriods[1] = { absenceAirT };
	DayProfile absenceDayAirTProfile(absenceAirTPeriods, 2);
	DayProfile absenceDaysAirTProfiles[7] = { absenceDayAirTProfile, absenceDayAirTProfile, absenceDayAirTProfile, absenceDayAirTProfile, absenceDayAirTProfile, absenceDayAirTProfile, absenceDayAirTProfile };
	WeekProfile absenceWeekAirTProfile(absenceDaysAirTProfiles, 7);
	TimeProfile absenceAirTProfile("ABSENCE", &absenceWeekAirTProfile);

	// TU_FR_Absense

	//TU_FR Absense day
	TimePeriod TUFR_AbsenceNightAirT(0, 1, 5, 0, 18);
	TimePeriod TUFR_AbsenceMonAirT(5, 1, 7, 0, 23);
	TimePeriod TUFR_AbsenceEvnAirT(7, 1, 23, 59, 2);
	TimePeriod TUFR_AbsenceAirTPeriods[3] = { TUFR_AbsenceNightAirT, TUFR_AbsenceMonAirT, TUFR_AbsenceEvnAirT };

	DayProfile TUFR_AbsenceDayAirTProfile(TUFR_AbsenceAirTPeriods, 2);


	//TU_FR After absense day
	TimePeriod TUFR_AfterAbsenseMonAirT(0, 1, 10, 00, 2);
	TimePeriod TUFR_AfterAbsenseEvnAirT(10, 1, 22, 00, 23);
	TimePeriod TUFR_AfterAbsenseNightAirT(22, 1, 23, 59, 18);
	TimePeriod TUFR_AfterAbsenseAirTPeriods[3] = { TUFR_AfterAbsenseMonAirT, TUFR_AfterAbsenseEvnAirT, TUFR_AfterAbsenseNightAirT };
	DayProfile TUFR_AfterAbsenceDayAirTProfile(TUFR_AfterAbsenseAirTPeriods, 2);


	//TU_FR Presense day
	TimePeriod TU_FR_Presense_Mon_AirT(0, 1, 6, 59, 18);
	TimePeriod  TU_FR_Presense_Day_AirT(7, 0, 23, 0, 23);
	TimePeriod  TU_FR_Presense_Evn_AirT(23, 1, 23, 59, 18);
	TimePeriod TU_FR_PresenseAirTPeriods[3] = { TU_FR_Presense_Mon_AirT, TU_FR_Presense_Day_AirT, TU_FR_Presense_Evn_AirT };
	DayProfile TUFR_PresenseAbsenceDayAirTProfile(TU_FR_PresenseAirTPeriods, 2);

	DayProfile TU_FR_DaysAirTProfiles[7] = {
		TUFR_PresenseAbsenceDayAirTProfile, 
		TUFR_AbsenceDayAirTProfile,
		TUFR_AfterAbsenceDayAirTProfile,
		TUFR_PresenseAbsenceDayAirTProfile,
		TUFR_AbsenceDayAirTProfile,
		TUFR_AfterAbsenceDayAirTProfile,
		TUFR_PresenseAbsenceDayAirTProfile
	};
	WeekProfile TU_FR_WeekAirTProfiles(TU_FR_DaysAirTProfiles, 7);
	TimeProfile TU_FR_AirTProfile("TU_FR_WEEKENDS", &TU_FR_WeekAirTProfiles);
	TimeProfile* airTProfiles[4] = {
		&presenceAirTProfile, 
		&absenceAirTProfile,
		&TU_FR_AirTProfile,
		&all_time_tuned_AirTProfile
	};
	
	*/
	



/*
//BAT TEMP PROFILES
TimePeriod presenceBatT(5, 0, 7, 0, &batFixTemp);
TimePeriod presenceBatTPeriods[1] = { presenceBatT };
DayProfile presenceDayBatTProfile(presenceBatTPeriods, 1);
DayProfile presenceDayBatTProfiles[7] = { presenceDayBatTProfile, presenceDayBatTProfile, presenceDayBatTProfile, presenceDayBatTProfile, presenceDayBatTProfile, presenceDayBatTProfile, presenceDayBatTProfile };
WeekProfile presenceWeekBatTProfile(presenceDayBatTProfiles, 7);
TimeProfile presenceBatTProfile("PRESENCE", &presenceWeekBatTProfile);
TimeProfile* batTProfiles[1] = { &presenceBatTProfile };
*/

/*
//LIGHT DAY SUN NiGHT OFF TIME PROFILE
TimePeriod WithoutNightLightEedgeDay(6, 0, 23, 59, &LightEdge);
TimePeriod WithoutNightLightEdgeNightBegin(0, 1, 5, 59, 9999);
TimePeriod WithoutNightLightEdgePeriods[2] = { WithoutNightLightEdgeNightBegin, WithoutNightLightEedgeDay };

DayProfile WithoutNightLightEdgeDayProfile(WithoutNightLightEdgePeriods, 3);
DayProfile WithoutNightLightEdgeDayProfiles[7] = {
	WithoutNightLightEdgeDayProfile,
	WithoutNightLightEdgeDayProfile,
	WithoutNightLightEdgeDayProfile,
	WithoutNightLightEdgeDayProfile,
	WithoutNightLightEdgeDayProfile,
	WithoutNightLightEdgeDayProfile,
	WithoutNightLightEdgeDayProfile
};
WeekProfile WithoutNightLightEdgeWeekProfile(WithoutNightLightEdgeDayProfiles, 7);
TimeProfile  WithoutNightLightEdgeProfile("DAY FIX NIGHT OFF", &WithoutNightLightEdgeWeekProfile);

//LIGHT ALL TIME PROFILE
TimePeriod AllDayLightEedgePeriod(0, 0, 23, 59, &LightEdge);

TimePeriod AllDayLightEdgePeriods[1] = { AllDayLightEedgePeriod };

DayProfile AllDayLightEdgeDayProfile(AllDayLightEdgePeriods, 1);
DayProfile AllDayLaightEdgeDayProfiles[7] = {
	AllDayLightEdgeDayProfile,
	AllDayLightEdgeDayProfile,
	AllDayLightEdgeDayProfile,
	AllDayLightEdgeDayProfile,
	AllDayLightEdgeDayProfile,
	AllDayLightEdgeDayProfile,
	AllDayLightEdgeDayProfile
};
WeekProfile AllDayLightEdgeWeekProfile(AllDayLaightEdgeDayProfiles, 7);
TimeProfile AllDaylightEdgeProfile("ALL TIME FIX", &AllDayLightEdgeWeekProfile);
TimeProfile* lightEdgeProfiles[2] = { &WithoutNightLightEdgeProfile, &AllDaylightEdgeProfile };



TimePeriod dryingAllDayTempPeriod(0, 0, 23, 59, &dryingFixTemp);

TimePeriod dryingAllDayTempPeriods[1] = { dryingAllDayTempPeriod };

DayProfile dryingAllDayTempDayProfile(dryingAllDayTempPeriods, 1);
DayProfile dryingAllDayTempDayProfiles[7] = {
	dryingAllDayTempDayProfile,
	dryingAllDayTempDayProfile,
	dryingAllDayTempDayProfile,
	dryingAllDayTempDayProfile,
	dryingAllDayTempDayProfile,
	dryingAllDayTempDayProfile,
	dryingAllDayTempDayProfile
};
WeekProfile dryingAllDayTempWeekProfile(dryingAllDayTempDayProfiles, 7);
TimeProfile dryingAllDayTempProfile("ALL TIME DRYING TEMP", &dryingAllDayTempWeekProfile);


TimePeriod dryingNightEndTempPeriod(0, 1, 6, 59, &dryingFixTemp);
TimePeriod dryingDayTempPeriod(7, 0, 22, 59, &dryingFixTemp);
TimePeriod dryingNightBeginTempPeriod(23, 0, 23, 59, &dryingFixTemp);
TimePeriod dryingNightOnTempPeriods[3] = { dryingNightEndTempPeriod, dryingDayTempPeriod, dryingNightBeginTempPeriod };
DayProfile dryingNightOnTempDayProfile(dryingNightOnTempPeriods, 1);
DayProfile dryingNightOnTempDayProfiles[7] = {
	dryingNightOnTempDayProfile,
	dryingNightOnTempDayProfile,
	dryingNightOnTempDayProfile,
	dryingNightOnTempDayProfile,
	dryingNightOnTempDayProfile,
	dryingNightOnTempDayProfile,
	dryingNightOnTempDayProfile
};
WeekProfile dryingNightOnTempWeekProfile(dryingNightOnTempDayProfiles, 7);
TimeProfile dryingNightOnTempProfile("NIGHT ON DRYING TEMP", &dryingNightOnTempWeekProfile);
TimeProfile* dryingTempProfiles[2] = { &dryingAllDayTempProfile, &dryingNightOnTempProfile };
std::vector< TimeProfile *> dryingTempProfilesV; */

#endif