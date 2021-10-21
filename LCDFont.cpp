#include "LCDFont.hpp"

LCDFont::LCDFont(const uint8_t* rusFont, 
	const uint8_t* engFont,
	const uint8_t size)
	: RusFont(rusFont)
	, EngFont(engFont)
	, Size(size)
{
}
