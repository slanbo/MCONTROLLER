
#include "Settings.hpp"
#include "i2c.h"
#include <string.h>
#include "I2C_LCD_1602.hpp"
#include "eeprom.h"
#include "stdlib.h"

int currentSetting = 0;

extern uint16_t currentSettings[SETTINGS_QUANT];
extern LCDScreen settingScreens[SETTINGS_SCREENS_COUNT];

uint16_t defaultSettings[SETTINGS_QUANT] = { 0, 0, 1, 1, 1, 0, 1, 0, 3, 0, 0 };
int settingsQuant[SETTINGS_QUANT] = { MODES_QUANT, AIR_TEMP_PROFILES_COUNT, YEAR_VARIANTS_COUNT, MONTH_VARIANTS_COUNT, DATE_VARIANTS_COUNT, HOUR_VARIANTS_COUNT, MINUTE_VARIANTS_COUNT, DAY_OF_WEEK_VARIANTS_COUNT, POWER_VARIANTS_COUNT, POWER_VARIANTS_COUNT, RESTORE_DEFAULTS_VARIANTS_COUNT };
char settingsNames[SETTINGS_QUANT][16] = { "MODE", "AIR TEMP. VAR.", "SET YEAR", "SET MONTH", "SET DATE", "SET HOUR", "SET MINUTE", "SET WEEK DAY", "UP HEATER PWR", "DOWN HEATER PWR", "RESTORE"};
char modesNames[MODES_QUANT][16] = { "TEMP. CONTROL"};
char airTempVariantsNames[AIR_TEMP_PROFILES_COUNT][16] = { "PRESENCE", "ABSENCE", "TU_FR_WEEKENDS" };
char batTempVariantsNames[BAT_TEMP_PROFILES_COUNT][16] = { "PRESENCE" };
char machVariantsNames[MASHINGS_COUNT][16] = { "35/45/50/63/70", "63/70" };
char boilVariantsNames[BOILINGS_COUNT][16] = { "90 min - 98 C", "60 min - 98 C"};
char tempVariantsNames[TEMPERATURE_VARIANTS_COUNT][16] = { "2 C", "3 C", "4 C", "5 C ANTIFROST", "6 C", "7 C", "8 C", "9 C", "10 C", "11 C", "12 C", "13 C", "14 C", "15 C", "16 C", "17 C", "18 C", "19 C", "20 C", "21 C", "22 C", "23 C COMFORT", "24 C", "25 C", "26 C" };
char yearVariantsNames[YEAR_VARIANTS_COUNT][16] = { "2020", "2021", "2022" };
char powerVariantsNames[POWER_VARIANTS_COUNT][16] = { "0 KVT", "0.5 KVT", "0.7 KVT", "1 KVT", "1.5 KVT", "2 KVT" };
char monthVariantsNames[MONTH_VARIANTS_COUNT][16] = { "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12" };
char dateVariantsNames[DATE_VARIANTS_COUNT][16] = { "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31" };
char hourVariantsNames[HOUR_VARIANTS_COUNT][16] = { "00", "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23" };
char minuteVariantsNames[MINUTE_VARIANTS_COUNT][16] = { "00", "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "40", "41", "42", "43", "44", "45", "46", "47", "48", "49", "50", "51", "52", "53", "54", "55", "56", "57", "58", "59" };
char dayOfWeekVariantsNames[DAY_OF_WEEK_VARIANTS_COUNT][16] = { "01", "02", "03", "04", "05", "06", "07" };
char restoreDefaultsVariantsNames[RESTORE_DEFAULTS_VARIANTS_COUNT][16] = { "KVT COUNTER", "DEFAULT SETTING", "GAS NULL LEVELS" };
char boilingVariantsTempStr[BOILINGS_COUNT][16] = { "98 C", "98 C"};
char boilingVariantsMinStr[BOILINGS_COUNT][16] = { "60 min", "70 min"};
uint8_t Temperatures[TEMPERATURE_VARIANTS_COUNT] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26 };
uint16_t Powers[POWER_VARIANTS_COUNT] = { 0, 500, 700, 1000, 1500, 2000 };

uint8_t yearVariants[YEAR_VARIANTS_COUNT] = { 20, 21, 22 };
uint8_t monthVariants[MONTH_VARIANTS_COUNT] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
uint8_t dateVariants[DATE_VARIANTS_COUNT] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 };
uint8_t hourVariants[HOUR_VARIANTS_COUNT] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23 };
uint8_t minuteVariants[MINUTE_VARIANTS_COUNT] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59 };
uint8_t dayOfWeekVariants[DAY_OF_WEEK_VARIANTS_COUNT] = { 1, 2, 3, 4, 5, 6, 7 };


void Write_Default_Setting_To_EEPROM()
{
	EE_Write_Array(CURRENT_SETTING_FLASH_ADDR, defaultSettings, SETTINGS_QUANT);
}

void Write_Current_Setting_To_EEPROM()
{
	EE_Write_Array(CURRENT_SETTING_FLASH_ADDR, currentSettings, SETTINGS_QUANT);
}

void Read_Current_Setting_From_EEPROM()
{
	EE_Read_Array(CURRENT_SETTING_FLASH_ADDR, currentSettings, SETTINGS_QUANT);
}

int getNextItemNumber(int currentItem, int maxItem)
{
	
	int NextItem;
	if (currentItem < maxItem - 1)
	{
		NextItem = currentItem + 1;
	}
	else
	{
		NextItem = 0;
	}
	return NextItem;

}

int getBeforeItemNumber(int currentItem, int maxItem)
{
	
	int BeforeItem;
	if (currentItem > 0)
	{
		BeforeItem = currentItem - 1;
	}
	else
	{
		BeforeItem = maxItem - 1;
	}
	return BeforeItem;

}

uint8_t getLCDModeByMode(uint8_t mode)
{
	return mode;
}

void updateSettinsScreen()
{
	strcpy(settingScreens[0].FirstString, settingsNames[currentSetting]); 
	switch (currentSetting)
	{
	case 0:
		strcpy(settingScreens[0].SecondString, modesNames[currentSettings[currentSetting]]);
		break;
	case 1:
		strcpy(settingScreens[0].SecondString, airTempVariantsNames[currentSettings[currentSetting]]);
		break;
	case 2:	
		strcpy(settingScreens[0].SecondString, yearVariantsNames[currentSettings[currentSetting]]);
		break;
	case 3:	
		strcpy(settingScreens[0].SecondString, monthVariantsNames[currentSettings[currentSetting]]);
		break;
	case 4:	
		strcpy(settingScreens[0].SecondString, dateVariantsNames[currentSettings[currentSetting]]);
		break;
	case 5:	
		strcpy(settingScreens[0].SecondString, hourVariantsNames[currentSettings[currentSetting]]);
		break;
	case 6:	
		strcpy(settingScreens[0].SecondString, minuteVariantsNames[currentSettings[currentSetting]]);
		break;	
	case 7:	
		strcpy(settingScreens[0].SecondString, dayOfWeekVariantsNames[currentSettings[currentSetting]]);
		break;	
	case 8:	
		strcpy(settingScreens[0].SecondString, powerVariantsNames[currentSettings[currentSetting]]);
		break;
	case 9:	
		strcpy(settingScreens[0].SecondString, powerVariantsNames[currentSettings[currentSetting]]);
		break;	
	case 10:	
		strcpy(settingScreens[0].SecondString, restoreDefaultsVariantsNames[currentSettings[currentSetting]]);
		break;
	default:
		strcpy(settingScreens[0].SecondString, "Undefined");
		break;
	}	
}



