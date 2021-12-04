#ifndef __SCREENELEMENT__H
#define __SCREENELEMENT__H

#include "main.h"
#include <string>
#include "LCDFont.hpp"

struct screenStyle
{
	uint16_t foreColor;
	uint16_t backColor;
	LCDFont& font;
};

class AbstractScreenElement
{
public:
	AbstractScreenElement() {};
	~AbstractScreenElement() {};
	
	virtual void Render() = 0;
	
	bool selected = false;
	
protected:
	
};

class BaseScreenElement : public AbstractScreenElement
{
public:
	BaseScreenElement(uint8_t left_x,
		uint8_t top_y,
		screenStyle * mainStyle,
		screenStyle * selectedStyle);
	
	BaseScreenElement(uint8_t left_x,
		uint8_t top_y,
		uint8_t right_x,
		uint8_t bottom_y,
		screenStyle * mainStyle,
		screenStyle * selectedStyle);
	
	~BaseScreenElement();
	
	virtual void Render() = 0;
	
	uint8_t Left_X = 0;
	uint8_t Top_Y = 0;
	
	uint8_t Right_X = 0;
	uint8_t Bottom_Y = 0;
	
	screenStyle * MainStyle;
	screenStyle * SelectedStyle;

	bool _getUpdated();
	void _setUpdated(bool Updated);
protected:
	bool updated = false;  //0-no 1-yes
private:	
	
};

class Text_ScreenElement : public BaseScreenElement
{
public:
	Text_ScreenElement(uint8_t left_x,
						uint8_t top_y,
						screenStyle * mainStyle,
						screenStyle * selectedStyle,
						const uint8_t maxLenght);
	~Text_ScreenElement();
	
	virtual void Render();

	void ClearText();
	void SetText(std::string text, bool convertToCp1251);
	void SetChars(const char* chars, bool convertToCp1251);
	void SetIntText(int dnum, uint8_t lenght);
	void FillEndBySpaces();
	char Text[MAX_CHARS_IN_SCREEN] = { 0 };
	
	
protected:
	const uint8_t MaxLenght;
	void SetRightBottomPoint(uint8_t right_x, uint8_t bottom_y);
	
private:
	uint8_t textLenght = 0;
	
};

class Rect_ScreenElement : public BaseScreenElement
{
public:
	Rect_ScreenElement(
					uint8_t left_x,
					uint8_t top_y,
					uint8_t right_x,
					uint8_t bottom_y,
					screenStyle * mainStyle,
					screenStyle * selectedStyle
					);
	~Rect_ScreenElement();
	
	virtual void Render();

	
protected:

	
};

#endif