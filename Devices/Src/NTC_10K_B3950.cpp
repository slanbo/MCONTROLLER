#include  "NTC_10K_B3950.hpp"
#include "ADCDevObjectsExt.hpp"

NTC_10K_B3950::NTC_10K_B3950(uint16_t ID,std::string name, uint8_t ADCDevID)
	: ADCSensor(ID, name, ADCDevID, TERMISTOR_TYPE_INDEX)
{
	UNITS[0] = 67;
	UNITS[1] = 176;
	UNITS[2] = ' ';
	UNITS[3] = 0;

}

uint16_t NTC_10K_B3950::getSensorUnits()
{
	return calc_temperature(adcDev->getAverageAdcResult());
}

uint16_t NTC_10K_B3950::calc_temperature(temperature_table_entry_type adcsum)
{
	temperature_table_index_type l = 0;
	temperature_table_index_type r = (sizeof(termo_table) / sizeof(termo_table[0])) - 1;
	temperature_table_entry_type thigh = termo_table[r];
  
	// Проверка выхода за пределы и граничных значений
	if(adcsum <= thigh) {
#ifdef TEMPERATURE_UNDER
		if (adcsum < thigh) 
			return TEMPERATURE_UNDER;
#endif
		return TEMPERATURE_TABLE_STEP * r + TEMPERATURE_TABLE_START;
	}
	temperature_table_entry_type tlow = termo_table[0];
	if (adcsum >= tlow) {
#ifdef TEMPERATURE_OVER
		if (adcsum > tlow)
			return TEMPERATURE_OVER;
#endif
		return TEMPERATURE_TABLE_START;
	}

	// Двоичный поиск по таблице
	while((r - l) > 1) {
		temperature_table_index_type m = (l + r) >> 1;
		temperature_table_entry_type mid = termo_table[m];
		if (adcsum > mid) {
			r = m;
		}
		else {
			l = m;
		}
	}
	temperature_table_entry_type vl = termo_table[l];
	if (adcsum >= vl) {
		return l * TEMPERATURE_TABLE_STEP + TEMPERATURE_TABLE_START;
	}
	temperature_table_entry_type vr = termo_table[r];
	temperature_table_entry_type vd = vl - vr;
	int16_t res = TEMPERATURE_TABLE_START + r * TEMPERATURE_TABLE_STEP; 
	if (vd) {
		// Линейная интерполяция
		res -= ((TEMPERATURE_TABLE_STEP * (int32_t)(adcsum - vr) + (vd >> 1)) / vd);
	}
	return res;
}
