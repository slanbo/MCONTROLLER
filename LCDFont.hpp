#pragma once
#include "main.h"
class LCDFont
{
public:
	LCDFont(const uint8_t* rusFont,
		const uint8_t* engFont,
		const uint8_t size);
	
	const uint8_t* RusFont;
	const uint8_t* EngFont;
	const uint8_t Size;
	
private:
};
