#include "Auxiliary.hpp"
#include "FreeRTOS.h"
#include "task.h"
#include "string.h"
#include "math.h"
#include "rtc.h"
#include "i2c.h"
#include "tim.h"
//#include <string>
//#include "stdlib.h"
#include "cmsis_os.h"
#include "time.h"

#include "stm32_ds3231.h"
#include "ds1307_for_stm32_hal.h"
#include "utf8_to_cp1251.h"



extern uint8_t currentBacklidht;

/* strlen: return length of string s */
int strlen(char *s)
{
	int i;
	while (*s++) i++;
	return i;
}

/* reverse:  reverse string s in place */
void reverse(char s[])
{
	int c, i, j;

	for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

/* itoa:  convert n to characters in s */
//void inttoabase10(int n, char s[])
int inttoabase10(int n, char s[]) 
{
	int i;
	if (n < 0) {
		n *= -1; 
	}

	i = 0;
	if (n / 10) {
		i = inttoabase10(n / 10, s);
	}
	s[i] = n % 10 + '0';
	s[++i] = '\0';

	return i; /* next free slot in array */
}

uint32_t getSeconds()
{
	return xTaskGetTickCount() / 1000;
}


void convert_Float_Parts_to_CharArr(char* fstr, char* dstr, float* num, uint8_t signs)
{
	//float f, s;
	//uint32_t level = 1;
	//for (uint8_t i = 1; i <= signs; i++)
	//{
	//	level = level * 10;
	//}
	//s = trunc(*num);
	
	//f = modf(*num, &s);
	//uint16_t d = (uint16_t)(f * level);
	//uint16_t fint = (uint16_t)s;
	inttoabase10((uint16_t)trunc(*num), fstr);
	inttoabase10(1, dstr);
}

void addDoubleString(char* str, double num, uint8_t signs)
{
	
	char strf[3] = { 0 };
	double f, s;
	
	f = modf(num, &s);
			
	uint32_t level = 1;
	
	for (uint8_t i = 1; i <= signs; i++)
	{
		level = level * 10;
	}
	
	  
	uint16_t d = (uint16_t)(f * level);
	uint16_t fint = (uint16_t)s;
	
	inttoabase10(fint, strf);
	
	strcat(str, strf);
	strcat(str, ".");
	addIntStr(str, d, signs);
}

void addIntStr(char* str, int dnum, uint8_t lenght)
{
	
	char dstr[lenght];
	
	uint16_t udint = dnum;
	uint16_t rsigns = 0;
	
	while (udint > 0)
	{
		udint = udint / 10;
		rsigns += 1;
	}
	
	inttoabase10(dnum, dstr);
	
	uint8_t zeros = lenght - rsigns;
	for (uint8_t i = 0; i < zeros; i++)
	{
		strcat(str, "0");
	}
	
	if (dnum > 0)
	{
		strcat(str, dstr);
	}
	
}

void GetWeekDayStr(uint8_t weekDayNumber, char* outStr)
{
	char tmp[4] = "";
	
	switch (weekDayNumber)
	{
	case 1:
		{
			strcpy(outStr, "DC"); 
			break;
		}
	case 2:
		{
			strcpy(outStr, "MN"); 
			break;
		}	
	case 3:
		{
			strcpy(outStr, "TU"); 
			break;
		}	
	case 4:
		{
			strcpy(outStr, "WD"); 
			break;
		}
	case 5:
		{
			strcpy(outStr, "TH"); 
			break;
		}
	case 6:
		{
			strcpy(outStr, "FR"); 
			break;
		}	
	case 7:
		{
			strcpy(outStr, "SA"); 
			break;
		}	
		
	}
}

void addCurrentDateString(char* str)
{
	
	char wdstr[2] = { 0 };
	
	RTC_TimeTypeDef sTime = { 0 };
	RTC_DateTypeDef sDate = { 0 };
	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	
	addIntStr(str, sDate.Date, 2);
	strcat(str, "/");
		
	addIntStr(str, sDate.Month, 2);
	strcat(str, "/");
		
	addIntStr(str, sDate.Year, 2);
	strcat(str, "/");

	GetWeekDayStr(sDate.WeekDay, wdstr);
	strcat(str, wdstr);
	
}

void addCurrentWeekDayTear(char* str)
{
	
	RTC_TimeTypeDef sTime = { 0 };
	RTC_DateTypeDef sDate = { 0 };
	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	
	char wdStrUtf8[5];
	GetWeekDayStr(sDate.WeekDay, wdStrUtf8);
	//char wdStrCP1251[2];
	//convertUtf8ToCp1251(wdStrUtf8, wdStrCP1251);
	
	strcat(str, wdStrUtf8);
	
	strcat(str, "/");
	addIntStr(str, sDate.Year + 2000, 4);
	
}

void addCurrentTimeString(char* str)
{
	RTC_TimeTypeDef sTime = { 0 };
	RTC_DateTypeDef sDate = { 0 };
	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	
	addIntStr(str, sTime.Hours, 2);
	strcat(str, ":");
		
	addIntStr(str, sTime.Minutes, 2);
	strcat(str, ":");
		
	addIntStr(str, sTime.Seconds, 2);
}

void DS1307_addCurrentDateString(char* str)
{
	
	_RTC rtc;
	bool success = DS3231_GetTime(&rtc);
	
	char strdate[2] = { 0 };
	char strmonth[2] = { 0 };
	char stryear[4] = { 0 };
		
	inttoabase10(rtc.Date, strdate);
	strcat(str, strdate);
	strcat(str, "/");
		
	inttoabase10(rtc.Month, strmonth);
	strcat(str, strmonth);
	strcat(str, "/");
		
	inttoabase10(rtc.Year, stryear);
	strcat(str, stryear);
	
		
	
}

void DS1307_addCurrentTimeString(char* str)
{
	
	_RTC rtc;
	bool success = DS3231_GetTime(&rtc);

	
	char strhours[2] = { 0 };
	char strminutes[2] = { 0 };
	char strseconds[2] = { 0 };
	
	inttoabase10(rtc.Hour, strhours);
	strcat(str, strhours);
	strcat(str, ":");
		
	inttoabase10(rtc.Min, strminutes);
	strcat(str, strminutes);
	strcat(str, ":");
		
	inttoabase10(rtc.Sec, strseconds);
	strcat(str, strseconds);
	
	
}


void addDateTimeString(char* str, uint16_t* dateArray)
{
		
	addIntStr(str, dateArray[2], 2);
	strcat(str, "/");
	addIntStr(str, dateArray[1], 2);
	strcat(str, "/");
	addIntStr(str, dateArray[0] - 2000, 2);
	
	strcat(str, " ");
	
	addIntStr(str, dateArray[3], 2);
	strcat(str, ":");
	addIntStr(str, dateArray[4], 2);
	
}

void I2C_send(uint8_t data, uint8_t flags)
{
	HAL_StatusTypeDef res;
	for (;  ;) {
		res = HAL_I2C_IsDeviceReady(&hi2c1, LCD_ADDR, 1, HAL_MAX_DELAY);               
		if (res == HAL_OK) break;                                                  
	}
	
	uint8_t up = data & 0xF0;   

	uint8_t lo = (data << 4) & 0xF0;          
                                          
	uint8_t data_arr[4];
	data_arr[0] = up | flags | currentBacklidht | PIN_EN;
	data_arr[1] = up | flags | currentBacklidht;         
	data_arr[2] = lo | flags | currentBacklidht | PIN_EN;
	data_arr[3] = lo | flags | currentBacklidht;

	HAL_I2C_Master_Transmit(&hi2c1, LCD_ADDR, data_arr, sizeof(data_arr), HAL_MAX_DELAY);
}

void US_DELAY(uint16_t time_us)
{
	htim1.Instance->CNT = 0;
	while (htim1.Instance->CNT <= time_us) ;
}


void LCD_Init()
{
	US_DELAY(50000);
	I2C_send(0b00110000, 0);        
	US_DELAY(50000);
	I2C_send(0b00000010, 0);        
	US_DELAY(50000);
	I2C_send(0b00001100, 0);        
	US_DELAY(50000);
	I2C_send(0b00000001, 0);        
	
}

void set_RTC_From_DS()
{
	
#ifdef USE_DS1307
	RTC_TimeTypeDef sTime = { 0 };
	RTC_DateTypeDef sDate = { 0 };
	
	sDate.Year = DS1307_GetYear() - 2000;
	sDate.Month = DS1307_GetMonth();
	sDate.Date = DS1307_GetDate();
	sDate.WeekDay = DS1307_GetDayOfWeek();
	
	sTime.Hours = DS1307_GetHour();
	sTime.Minutes = DS1307_GetMinute();
	sTime.Seconds = DS1307_GetSecond();
	
	HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);	
#endif // USE_DS1307
#ifdef USE_DS3231
	_RTC rtc = { 0 };
	bool success = DS3231_GetTime(&rtc);
	
	RTC_TimeTypeDef sTime = { 0 };
	RTC_DateTypeDef sDate = { 0 };
	
	sDate.Year = rtc.Year;
	sDate.Month = rtc.Month;
	sDate.Date = rtc.Date;
	sDate.WeekDay = rtc.DaysOfWeek;
	
	sTime.Hours = rtc.Hour;
	sTime.Minutes = rtc.Min;
	sTime.Seconds = rtc.Sec;
	
	HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

#endif // USE_DS3231

	
}

void set_DS_From_RTC()
{
	
#ifdef USE_DS1307
	RTC_TimeTypeDef sTime = { 0 };
	RTC_DateTypeDef sDate = { 0 };
	
	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

	DS1307_SetYear(sDate.Year + 2000);
	DS1307_SetMonth(sDate.Month);
	DS1307_SetDate(sDate.Date);
	DS1307_SetDayOfWeek(sDate.WeekDay);
	
	DS1307_SetHour(sTime.Hours);
	DS1307_SetMinute(sTime.Minutes);
	DS1307_SetSecond(sTime.Seconds);
# endif // USE_DS1307
#ifdef USE_DS3231
	_RTC rtc;
	
	RTC_TimeTypeDef sTime = { 0 };
	RTC_DateTypeDef sDate = { 0 };
	
	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

	rtc.Year = sDate.Year;
	rtc.Month = sDate.Month;
	rtc.Date = sDate.Date;
	rtc.DaysOfWeek = sDate.WeekDay;
	
	rtc.Hour = sTime.Hours;
	rtc.Min = sTime.Minutes;
	rtc.Sec = sTime.Seconds;
	
	bool success = DS3231_SetTime(&rtc);
#endif // USE_DS3231
}

enum compareRes CompareDates(RTC_DateTypeDef* fDate, RTC_TimeTypeDef* fTime, RTC_DateTypeDef* sDate, RTC_TimeTypeDef* sTime)
{
	if(fDate->Year < sDate->Year)
		return LESS ;
	else if(sDate->Year > sDate->Year)
		return MORE ;
	
	//month
	if(fDate->Month < sDate->Month)
		return LESS ;
	else if(fDate->Month > sDate->Month)	
		return MORE ;
	
	//date
	if(fDate->Date < sDate->Date)
		return LESS ;
	else if(fDate->Date > sDate->Date)	
		return MORE ;
	
	//hour
	if(fTime->Hours < sTime->Hours)
		return LESS ;
	else if(fTime->Hours > sTime->Hours)	
		return MORE ;	
	
	//minute
	if(fTime->Minutes < sTime->Minutes)
		return LESS ;
	else if(fTime->Minutes > sTime->Minutes)	
		return MORE ;
	
	return EQUAL ;
}
;

time_t getCurrentSecondsFromBegin()
{
	RTC_DateTypeDef dt;
	RTC_TimeTypeDef tt;
	
	HAL_RTC_GetTime(&hrtc, &tt, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &dt, RTC_FORMAT_BIN); 
	
	struct tm fcl;
	time_t Ftim = 0;           // this is undigned int
	fcl.tm_hour = tt.Hours;
	fcl.tm_min = tt.Minutes;
	fcl.tm_sec = tt.Seconds;
	fcl.tm_mday = dt.Date;
	fcl.tm_mon = dt.Month - 1;
	fcl.tm_year = dt.Year + 2000 - 1900;
	fcl.tm_wday = dt.WeekDay;	
	return my_timegm(&fcl);  // tim
}
;


uint8_t AddIntChars(char* text, int dnum, uint8_t lenght, char fillChar = ' ')
{
	uint8_t res_lenght = 0;
	char dstr[lenght];
	uint16_t udint = dnum;
	uint16_t rsigns = 0;
	
	while (text[res_lenght] != 0)
		res_lenght++;
	
	if (dnum != 0)
	{
		while (udint > 0)
		{
			udint = udint / 10;
			rsigns++;
		}
		inttoabase10(dnum, dstr);
		if (lenght > 0)
		{
			uint8_t zeros = lenght - rsigns;
			for (uint8_t i = 0; i < zeros; i++)
			{
				text[res_lenght] = fillChar;
				res_lenght++;
			}
		}
		for (uint8_t i = 0; i < rsigns; i++)
		{
			text[res_lenght] = dstr[i];
			res_lenght++;
		}
		text[res_lenght] = 0;
	}
	else
	{
		for (uint8_t i = 0; i < lenght - 1; i++)
		{
			text[res_lenght] = fillChar;	
			res_lenght++;
		}
		text[res_lenght] = '0';	
		res_lenght++;
		text[res_lenght] = 0;
	}
	return res_lenght;
}


uint8_t FillEndBySpaces(char* text, uint8_t lenght)
{
	uint8_t res_lenght = 0;
	while (text[res_lenght] != 0)
		res_lenght++;

	
	for (uint8_t i = res_lenght; i < lenght - 1; i++)
	{
		text[res_lenght] = ' ';	
		res_lenght++;
	}
	text[res_lenght] = 0;	
	return res_lenght;
}

uint8_t AddChars(char* text, const char* chars, bool convertToCp1251)
{
	uint8_t res_lenght = 0;
	char converted_charptr[16] = { 0 };
	uint8_t counter;
	
	uint8_t in_lenght = 0;
	if (convertToCp1251)
		in_lenght = convertUtf8ToCp1251(chars, converted_charptr);
	else
	{
		while (chars[in_lenght] != 0)
		{
			converted_charptr[in_lenght] = chars[in_lenght];
			in_lenght++;
		}	
		converted_charptr[in_lenght + 1] = '\0';
	}
	
	
	while (text[res_lenght] != 0)
		res_lenght++;
	
	counter = 0;
	while (converted_charptr[counter] != 0)
	{
		text[res_lenght] = converted_charptr[counter];
		counter++;
		res_lenght++;
	}
	text[res_lenght] = 0;
	
	return res_lenght;

}

static char * _float_to_char(float x, char *p)
{
	char *s = p + CHAR_BUFF_SIZE;     // go to end of buffer
	uint16_t decimals;      // variable to store the decimals
	int BaseUnits;      // variable to store the BaseUnits (part to left of decimal place)
	if(x < 0) {
		// take care of negative numbers
	   decimals = (int)(x * -100) % 100;     // make 1000 for 3 decimals etc.
	   BaseUnits = (int)(-1 * x);
	} else {
		// positive numbers
	   decimals = (int)(x * 100) % 100;
		BaseUnits = (int)x;
	}

	* --s = (decimals % 10) + '0';
	decimals /= 10;     // repeat for as many decimal places as you need
	* --s = (decimals % 10) + '0';
	* --s = '.';

	while (BaseUnits > 0) {
		* --s = (BaseUnits % 10) + '0';
		BaseUnits /= 10;
	}
	if (x < 0) * --s = '-';     // unary minus sign for negative numbers
	return s;
}
;	 
	 

time_t my_timegm( struct tm * t)
/* struct tm to seconds since Unix epoch */
{
	long year;
	time_t result;
	#define MONTHSPERYEAR   12      /* months per calendar year */
	static const int cumdays[MONTHSPERYEAR] =
	    { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };

	/*@ +matchanyintegral @*/
	year = 1900 + t->tm_year + t->tm_mon / MONTHSPERYEAR;
	result = (year - 1970) * 365 + cumdays[t->tm_mon % MONTHSPERYEAR];
	result += (year - 1968) / 4;
	result -= (year - 1900) / 100;
	result += (year - 1600) / 400;
	if ((year % 4) == 0 && ((year % 100) != 0 || (year % 400) == 0) &&
	    (t->tm_mon % MONTHSPERYEAR) < 2)
		result--;
	result += t->tm_mday - 1;
	result *= 24;
	result += t->tm_hour;
	result *= 60;
	result += t->tm_min;
	result *= 60;
	result += t->tm_sec;
	if (t->tm_isdst == 1)
		result -= 3600;
	/*@ -matchanyintegral @*/
	return (result);
}
