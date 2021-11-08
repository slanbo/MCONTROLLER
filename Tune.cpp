#include "Tune.hpp"




//########################### flash tune
uint16_t FlashTune::clear()
{
	uint16_t Status = 0;
	for (uint8_t i = 0; i < size; i++)
	{
		HAL_FLASH_Unlock();
		Status = EE_WriteVariable(FlashAddress + i, 0);
		HAL_FLASH_Lock();
	}
	return Status;
}


FlashTune::FlashTune(FlashTune * prevFlashTune)
	: PrevFlashTune(prevFlashTune)
{
	if (prevFlashTune == nullptr)
	{
		FlashAddress = FIRST_FLASH_ADDRESS;
	}
	
	if (prevFlashTune != nullptr & prevFlashTune->FlashAddress != 0)
	{
		FlashAddress = prevFlashTune->FlashAddress + prevFlashTune->size;
	}

}

uint8_t FlashTune::getSize()
{
	return size;
}

FlashTune * FlashTune::getPrevFlashTune()
{
	return PrevFlashTune;
}

//#################### int tune
intTune::intTune(FlashTune * prevFlashTune)
	: FlashTune(prevFlashTune)
{
}
;
	
uint16_t intTune::save()
{
	uint16_t Status;
	HAL_FLASH_Unlock();
	Status = EE_WriteVariable(FlashAddress, val);
	HAL_FLASH_Lock();
	return Status;
}

uint16_t intTune::restore()
{
	uint16_t Status;
	Status = EE_ReadVariable(FlashAddress, &val);
	return Status ;
}

uint16_t intTune::_getVal()
{
	return val;
}

void intTune::_setVal(uint16_t Val)
{
	val = Val;
	save();

}

bool intTune::undefined()
{
	if (val == 0)
		return true;
	else
		return false;
}


//############### date tune
uint16_t DateTune::save()
{
	
	RTC_DateTypeDef sDate = { 0 };
	RTC_TimeTypeDef sTime = { 0 };
	switch (DateTimePart)
	{
	case DateTimeParts::YEAR:
		sDate.Year = val - 2000;
		break;
	case 	DateTimeParts::MONTH:
		sDate.Month = val;
		break;
	case 	DateTimeParts::DATE:
		sDate.Date = val;
		break;
	case 	DateTimeParts::HOUR:
		sTime.Hours = val;
		break;
	case 	DateTimeParts::MINUTE:
		sTime.Minutes = val;
		break;
	case 	DateTimeParts::SECOND:
		sTime.Seconds = val;
		break;
	case 	DateTimeParts::WEEKDAY:
		sDate.WeekDay = val;
		break;
	default: 
		break;
	}
	HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	return 0;
}

uint16_t DateTune::restore()
{
	RTC_DateTypeDef sDate = { 0 };
	RTC_TimeTypeDef sTime = { 0 };
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	
	switch (DateTimePart)
	{
	case DateTimeParts::YEAR:
		val = sDate.Year + 2000;
		break;
	case 	DateTimeParts::MONTH:
		val = sDate.Month;
		break;
	case 	DateTimeParts::DATE:
		val = sDate.Date;
		break;
	case 	DateTimeParts::HOUR:
		val = sTime.Hours;
		break;
	case 	DateTimeParts::MINUTE:
		val = sTime.Minutes;
		break;
	case 	DateTimeParts::SECOND:
		val = sTime.Seconds;
		break;
	case 	DateTimeParts::WEEKDAY:
		val = sDate.WeekDay;
		break;
	default: 
		break;
	}

	return 0;
}

uint16_t DateTune::clear()
{
	return 0;
}


DateTune::DateTune(DateTimeParts dateTimePart)
	: DateTimePart(dateTimePart)
{
	
}

bool DateTune::undefined()
{
	return false;
}

//############ int vector tune
IntVectorTune::IntVectorTune(FlashTune * prevFlashTune, 
	uint16_t Size)
	: FlashTune(prevFlashTune)
{
	val.resize(size);
	for (auto item : val)
		item = 0;
}

IntVectorTune::IntVectorTune(FlashTune * prevFlashTune, 
	uint16_t Size, 
	std::vector<uint16_t> &defs)
	: FlashTune(prevFlashTune)


{
	val.resize(size);
	uint8_t counter = 0;
	for (auto def : defs)
	{
		if (val[counter] == 0)
		{
			val[counter] = def;
		}
		counter++;
	}
}


uint16_t IntVectorTune::_getVal(uint16_t index)
{
	return val[index];
}


void IntVectorTune::_setVal(uint16_t Val, uint16_t index)
{
	val[index] = Val;
	save();
}


uint16_t IntVectorTune::save()
{
	uint16_t Status;
	HAL_FLASH_Unlock();
	uint8_t offset = 0;
	for (auto item : val)
	{
		Status = EE_WriteVariable(FlashAddress + offset, item);
		offset++;
	}
	
	HAL_FLASH_Lock();
	return Status;
	
}


uint16_t IntVectorTune::restore()
{
	
	uint16_t Status;
	uint8_t offset = 0;
	for (auto item : val)
	{
		Status = EE_ReadVariable(FlashAddress, &item);
		offset++;
	}
	return Status;
}

bool IntVectorTune::undefined()
{
	bool undef = true;
	for (auto item : val)
	{
		if (item != 0)
			undef = true;
	}
	
	return undef;
}


std::vector<uint16_t>&  IntVectorTune::_getVal()
{
	uint16_t Status;
	uint8_t offset = 0;
	for (auto item : val)
	{
		Status = EE_ReadVariable(FlashAddress, &item);
		offset++;
	}
	//Status = restore();
	return val;
}


void IntVectorTune::_setVal(std::vector<uint16_t> &Val)
{
	
	uint8_t counter = 0;
	for (auto item : Val)
		val[counter] = item;
	save();
		
}
