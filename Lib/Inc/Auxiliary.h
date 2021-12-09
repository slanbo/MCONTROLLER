#pragma once
#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"
#include "time.h"
	 
	 enum compareRes
	 {
		 LESS,
		 MORE,
		 EQUAL
	 };	 
	 
#define PIN_EN    (1 << 2)         // бит, по изменению сост. которого считывается информация
	 
int inttoabase10(int n, char s[]);
int inttoa(int value, char *sp, int radix);
uint32_t getSeconds();
void convert_Float_Parts_to_CharArr(char* fstr, char* dstr, float* num, uint8_t signs);
void addDoubleString(char* str, double num, uint8_t signs);
void addCurrentDateString(char* str);
void addCurrentTimeString(char* str);	 
void DS1307_addCurrentDateString(char* str);
void DS1307_addCurrentTimeString(char* str);	
void addDateTimeString(char* str, uint16_t* date);	 
void addCurrentWeekDayTear(char* str); 
void LCD_Init();
void I2C_send(uint8_t data, uint8_t flags);
void US_DELAY(uint16_t time_us);
void set_RTC_From_DS();
void set_DS_From_RTC();	 
void addIntStr(char* str, int dnum, uint8_t lenght);	 
enum compareRes CompareDates(RTC_DateTypeDef* fDate, RTC_TimeTypeDef* fTime, RTC_DateTypeDef* sDate, RTC_TimeTypeDef* sTime);	
	 time_t getSecondsFromBegin(RTC_DateTypeDef* fDate, RTC_TimeTypeDef* fTime);
	 
static char * _float_to_char(float x, char *p)
	 {
		 char *s = p + CHAR_BUFF_SIZE;   // go to end of buffer
		 uint16_t decimals;    // variable to store the decimals
		 int BaseUnits;    // variable to store the BaseUnits (part to left of decimal place)
		 if(x < 0) {
			 // take care of negative numbers
			decimals = (int)(x * -100) % 100;   // make 1000 for 3 decimals etc.
			BaseUnits = (int)(-1 * x);
		 } else {
			 // positive numbers
			decimals = (int)(x * 100) % 100;
			 BaseUnits = (int)x;
		 }

		 * --s = (decimals % 10) + '0';
		 decimals /= 10;   // repeat for as many decimal places as you need
		 * --s = (decimals % 10) + '0';
		 * --s = '.';

		 while (BaseUnits > 0) {
			 * --s = (BaseUnits % 10) + '0';
			 BaseUnits /= 10;
		 }
		 if (x < 0) * --s = '-';   // unary minus sign for negative numbers
		 return s;
	 }
	 ;	 
	 
#ifdef __cplusplus
}
#endif