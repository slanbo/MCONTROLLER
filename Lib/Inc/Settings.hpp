#include "main.h"
#include "I2C_LCD_1602.hpp"


#define SETTINGS_QUANT 11
#define MODES_QUANT 1

#define CURRENT_SETTING_BEGIN_ADDR 0x0100
#define TEMPERATURE_VARIANTS_COUNT 25
#define POWER_VARIANTS_COUNT 6
#define RESTORE_DEFAULTS_VARIANTS_COUNT 3


#define YEAR_VARIANTS_COUNT 3
#define MONTH_VARIANTS_COUNT 12
#define DATE_VARIANTS_COUNT 31
#define HOUR_VARIANTS_COUNT 24
#define MINUTE_VARIANTS_COUNT 60
#define DAY_OF_WEEK_VARIANTS_COUNT 7


#define PAUSES 5
#define BOILING_PAUSES 1

#define ROOM_CONTROL_LCD_MODE  0
#define MASHING_LCD_MODE  1
#define BOILING_LCD_MODE  2
#define SETTINGS_LCD_MODE  3
#define START_LCD_MODE  4

#define MODES_SETTINGS_INDEX 0

#define ROOM_CONTROL_AIR_TEMPERATURE_SETTINGS_INDEX 1
//#define ROOM_CONTROL_BAT_TEMPERATURE_SETTINGS_INDEX 2

//#define MASHING_VARIANTS_SETTINGS_INDEX 3
//#define BOILING_VARIANTS_SETTINGS_INDEX 4

#define YEAR_VARIANTS_INDEX 2
#define MONTH_VARIANTS_INDEX 3
#define DATE_VARIANTS_INDEX 4
#define HOUR_VARIANTS_INDEX 5
#define MINUTE_VARIANTS_INDEX 6
#define DAY_OF_WEEK_VARIANTS_INDEX 7

#define UP_POWER_VARIANTS_INDEX 8
#define DOWN_POWER_VARIANTS_INDEX 9


#define RESTORE_DEFAULTS_INDEX 10

#define RESTORE_KVT_COUNTER_DEFAULTS_INDEX 0
#define RESTORE_SETTINGS_DEFAULTS_INDEX 1
#define GAS_NULL_LEVELS_INDEX 2



#define MASHINGS_COUNT 2
#define BOILINGS_COUNT 2

#define AIR_TEMP_PROFILES_COUNT 3
#define BAT_TEMP_PROFILES_COUNT 1

#define CURRENT_SETTING_FLASH_ADDR 0x0001

extern int currentSetting;



//extern LCDScreen settingScreens[SETTINGS_SCREENS_COUNT];
//extern i2c_LCD_1602 settingsScreen;

extern LCDScreen settingScreensBuffer[SETTINGS_SCREENS_COUNT];


extern uint16_t defaultSettings[SETTINGS_QUANT];
extern int settingsQuant[SETTINGS_QUANT];
extern char settingsNames[SETTINGS_QUANT][16];
extern char modesNames[MODES_QUANT][16];
extern char machVariantsNames[MASHINGS_COUNT][16];
extern char boilVariantsNames[BOILINGS_COUNT][16];
extern char tempVariantsNames[TEMPERATURE_VARIANTS_COUNT][16];
extern char yearVariantsNames[YEAR_VARIANTS_COUNT][16];
extern char powerVariantsNames[POWER_VARIANTS_COUNT][16];
extern char monthVariantsNames[MONTH_VARIANTS_COUNT][16];
extern char dateVariantsNames[DATE_VARIANTS_COUNT][16];
extern char hourVariantsNames[HOUR_VARIANTS_COUNT][16];
extern char minuteVariantsNames[MINUTE_VARIANTS_COUNT][16];
extern char dayOfWeekVariantsNames[DAY_OF_WEEK_VARIANTS_COUNT][16];

extern char restoreDefaultsVariantsNames[RESTORE_DEFAULTS_VARIANTS_COUNT][16];
extern char mashingVariantsTempStr[MASHINGS_COUNT][16];
extern char mashingVariantsMinStr[MASHINGS_COUNT][16];
extern uint8_t pausesMinutesAim[MASHINGS_COUNT][PAUSES];
extern uint8_t pausesTemperatures[MASHINGS_COUNT][PAUSES];
extern char boilingVariantsTempStr[BOILINGS_COUNT][16];
extern char boilingVariantsMinStr[BOILINGS_COUNT][16];
extern double boilingPausesMinutesAim[BOILINGS_COUNT][BOILING_PAUSES];
extern uint8_t boilingPausesTemperatures[BOILINGS_COUNT][BOILING_PAUSES];
extern uint8_t Temperatures[TEMPERATURE_VARIANTS_COUNT];
extern uint16_t Powers[POWER_VARIANTS_COUNT];

extern char airTempVariantsNames[AIR_TEMP_PROFILES_COUNT][16];
extern char batTempVariantsNames[BAT_TEMP_PROFILES_COUNT][16];

extern uint8_t yearVariants[YEAR_VARIANTS_COUNT];
extern uint8_t monthVariants[MONTH_VARIANTS_COUNT];
extern uint8_t dateVariants[DATE_VARIANTS_COUNT];
extern uint8_t hourVariants[HOUR_VARIANTS_COUNT];
extern uint8_t minuteVariants[MINUTE_VARIANTS_COUNT];
extern uint8_t dayOfWeekVariants[DAY_OF_WEEK_VARIANTS_COUNT];


int getNextItemNumber(int currentItem, int maxItem);
int getBeforeItemNumber(int currentItem, int maxItem);
void Write_Current_Setting_To_EEPROM();
void Read_Current_Setting_From_EEPROM();
void Write_Default_Setting_To_EEPROM();
void proccedButtonPress();
void updateSettinsScreen();