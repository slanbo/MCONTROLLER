
#ifndef __TUNE_CLASS_H
#define __TUNE_CLASS_H

#include "eeprom.h"
#include "rtc.h"
#include <vector>

enum class DateTimeParts
{
	YEAR,
	MONTH,
	DATE,
	HOUR,
	MINUTE,
	SECOND,
	WEEKDAY
}
;

class TuneBase
{
public:
	
	virtual uint16_t save() = 0;
	virtual uint16_t restore() = 0;
	virtual bool undefined() = 0;

protected:
	
};

class FlashTune : public TuneBase
{
public:
	
	FlashTune(FlashTune * prevFlashTune);
	FlashTune(FlashTune * prevFlashTune, uint8_t Size);
	
	virtual uint16_t clear();
	uint8_t getSize();
	FlashTune * getPrevFlashTune();
	
	uint16_t getFlashAddress();
	
protected:
	
	FlashTune * PrevFlashTune = nullptr;
	uint16_t FlashAddress = 0xffff;
	uint8_t size = 1; 
	
};

class intTune : public FlashTune
{
public:
	intTune(FlashTune * prevFlashTune);
		
	virtual uint16_t save();
	virtual uint16_t restore();
	virtual bool undefined();
	
	//getters setters
	uint16_t _getVal();
	void _setVal(uint16_t Val);
	
protected:
	
private:
	uint16_t val = 0;
};

class DateTune : public TuneBase
{
public:
	
	DateTune(DateTimeParts dateTimePart);
	virtual uint16_t save();
	virtual uint16_t restore();
	virtual uint16_t clear();
	
	virtual bool undefined();
	
	uint16_t _getVal();
	void _setVal(uint16_t Val);

	
protected:
	
private:	
	DateTimeParts DateTimePart;
	uint16_t val;
	
};

class IntVectorTune : public FlashTune
{
public:
	IntVectorTune(FlashTune * prevFlashTune, uint8_t Size);
	
	IntVectorTune(FlashTune * prevFlashTune, uint8_t Size, std::vector<uint16_t> &defs);
	
	virtual uint16_t save();
	virtual uint16_t restore();
	
	virtual bool undefined();

	
	//getters setters
	
	uint16_t _getVal(uint16_t index);
	void _getVal();
	void _setVal(uint16_t Val, uint16_t index);
	void _setVal(std::vector<uint16_t> &Val);
	
	std::vector<uint16_t> val;

	
protected:
	
	
};


#endif





