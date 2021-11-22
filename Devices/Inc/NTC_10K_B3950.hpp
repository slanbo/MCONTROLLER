#pragma once
#include "gpio.h"
#include "adc.h"
#include "ADCSensorDev.hpp"


#define TEMPERATURE_UNDER -55
// Значение температуры, возвращаемое если сумма результатов АЦП меньше последнего значения таблицы
#define TEMPERATURE_OVER 125
// Значение температуры соответствующее первому значению таблицы
#define TEMPERATURE_TABLE_START -55
// Шаг таблицы 
#define TEMPERATURE_TABLE_STEP 5

// Тип каждого элемента в таблице, если сумма выходит в пределах 16 бит - uint16_t, иначе - uint32_t
typedef uint16_t temperature_table_entry_type;
// Тип индекса таблицы. Если в таблице больше 256 элементов, то uint16_t, иначе - uint8_t
typedef uint8_t temperature_table_index_type;

// Метод доступа к элементу таблицы, должна соответствовать temperature_table_entry_type
//#define TEMPERATURE_TABLE_READ(i) pgm_read_word(&termo_table[i])

/* Таблица суммарного значения АЦП в зависимости от температуры. От большего значения к меньшему
   Для построения таблицы использованы следующие парамертры:
     R1(T1): 22кОм(25°С)
     R2(T2): 1.211034кОм(100°С)
     Схема включения: A
     Ra: 10кОм
     Напряжения U0/Uref: 3.3В/3.3В
*/
const temperature_table_entry_type termo_table[] = {
	4050,
	4031,
	4005,
	3970,
	3925,
	3867,
	3794,
	3703,
	3591,
	3459,
	3301,
	3121,
	2926,
	2716,
	2497,
	2273,
	2048,
	1831,
	1624,
	1431,
	1256,
	1098,
	955,
	829,
	719,
	623,
	540,
	468,
	406,
	353,
	307,
	267,
	233,
	204,
	179,
	157,
	139,
	123,
	108,
	96,
	85,
	76,
	68
};

class NTC_10K_B3950 : public ADCSensor
{
private:
	uint16_t calc_temperature(temperature_table_entry_type adcsum);
public:
	NTC_10K_B3950(uint16_t ID, std::string name, uint8_t ADCDevID);
	virtual uint16_t getSensorBaseUnits();
};
