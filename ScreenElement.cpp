#include "ScreenElement.hpp"
#include "GUI.h"
#include "utf8_to_cp1251.h" 
#include "Auxiliary.hpp"

BaseScreenElement::BaseScreenElement(uint8_t left_x, 
	uint8_t top_y, 
	screenStyle * mainStyle,
	screenStyle * selectedStyle)
	: MainStyle(mainStyle)
	, Left_X(left_x)
	, Top_Y(top_y)
	, SelectedStyle(selectedStyle)
{
}

BaseScreenElement::BaseScreenElement(uint8_t left_x, 
	uint8_t top_y, 
	screenStyle * mainStyle,
	screenStyle * selectedStyle,
	screenStyle * markedStyle)
	: MainStyle(mainStyle)
	, Left_X(left_x)
	, Top_Y(top_y)
	, SelectedStyle(selectedStyle)
	, MarkedStyle(markedStyle)
	
{
}

BaseScreenElement::BaseScreenElement(uint8_t left_x, 
	uint8_t top_y, 
	uint8_t right_x, 
	uint8_t bottom_y, 
	screenStyle * mainStyle,
	screenStyle * selectedStyle)
	: Left_X(left_x)
	, Top_Y(top_y)
	, Right_X(right_x)
	, Bottom_Y(bottom_y)
	, MainStyle(mainStyle)
	, SelectedStyle(selectedStyle)
{
}

BaseScreenElement::BaseScreenElement(uint8_t left_x, 
	uint8_t top_y, 
	uint8_t right_x, 
	uint8_t bottom_y, 
	screenStyle * mainStyle,
	screenStyle * selectedStyle,
	screenStyle * markedStyle)
	: Left_X(left_x)
	, Top_Y(top_y)
	, Right_X(right_x)
	, Bottom_Y(bottom_y)
	, MainStyle(mainStyle)
	, SelectedStyle(selectedStyle)
	, MarkedStyle(markedStyle)
{
}



BaseScreenElement::~BaseScreenElement()
{
}

Text_ScreenElement::Text_ScreenElement(uint8_t left_x, 
	uint8_t top_y, 
	screenStyle * mainStyle,
	screenStyle * selectedStyle,
	const uint8_t maxLenght)
	: BaseScreenElement(left_x, top_y, mainStyle, selectedStyle) 
	, MaxLenght(maxLenght)
{
	
}

Text_ScreenElement::Text_ScreenElement(uint8_t left_x, 
	uint8_t top_y, 
	screenStyle * mainStyle,
	screenStyle * selectedStyle,
	screenStyle * maekedStyle,
	const uint8_t maxLenght)
	: BaseScreenElement(left_x, top_y, mainStyle, selectedStyle, maekedStyle) 
	, MaxLenght(maxLenght)
{
}

Text_ScreenElement::~Text_ScreenElement()
{
}

void Text_ScreenElement::Render()
{
	if (_getUpdated())
	{
		screenStyle* currentStyle = MainStyle;
		if (selected)
			currentStyle = SelectedStyle;
		
		
		if (marked)
			if(MarkedStyle != nullptr)
			currentStyle = MarkedStyle;
	
		uint8_t deltaLenght = 0;
	
		if (textLenght > MaxLenght)
		{
			textLenght = MaxLenght;
			deltaLenght = 0;
		}
		else
			deltaLenght = MaxLenght - textLenght;
	
		uint8_t endxpos = PutChangedCharsToLCD(
		Left_X,
			Top_Y,
			currentStyle->foreColor,
			currentStyle->backColor,
			Text,
			textLenght,
			currentStyle->font.RusFont,
			currentStyle->font.EngFont,
			currentStyle->font.Size,
			1);
	
		//if (deltaLenght > 0)
		//	LCD_DrawFillRectangle(endxpos, Top_Y, endxpos + deltaLenght * (currentStyle->font.Size + 1), Top_Y + currentStyle->font.Size, currentStyle->backColor);
		//SetRightBottomPoint(endxpos + deltaLenght * (currentStyle->font.Size + 2), Top_Y + currentStyle->font.Size);
		_setUpdated(false);
	}
	
	
}

void Text_ScreenElement::SetRightBottomPoint(uint8_t right_x, uint8_t bottom_y)
{
	if (right_x > Right_X)
		Right_X = right_x;
	if (bottom_y > Bottom_Y)
		Bottom_Y = bottom_y;
}

void Text_ScreenElement::ClearText()
{
	uint8_t counter = 0;
	while (counter < MaxLenght)
	{
		Text[counter] = '\0';
		counter++;
	}
	textLenght = 0;

}

void Text_ScreenElement::SetChars(const char* chars, bool convertToCp1251)
{
	char converted_charptr[FONT_12_MAX_SIMVOLS_IN_STRING] = { 0 };
	uint8_t counter ;
	
	if (convertToCp1251)
		convertUtf8ToCp1251(chars, converted_charptr);
	else
	{
		counter = 0;
		while (chars[counter] != 0)
		{
			converted_charptr[counter] = chars[counter];
			counter++;
		}	
		counter++;
		converted_charptr[counter] = '\0';
	}
	
	counter = 0;
	while (converted_charptr[counter] != 0)
	{
		if (textLenght < MaxLenght - 1)
		{
			Text[textLenght] = converted_charptr[counter];
			counter++;
			textLenght++;
		}
		else
			break;
	}
	Text[textLenght + 1] = '\0';
}


void Text_ScreenElement::SetText(const char* text, bool convertToCp1251)
{
	/*const char* charptr = text.c_str();
	
	if (convertToCp1251)
	{
		uint8_t lenght = convertUtf8ToCp1251(charptr, Text);
		textLenght = textLenght + lenght;
	}
	else
	{
		uint8_t counter = 0;
		while (charptr[counter] != 0)
		{
			Text[textLenght] = charptr[counter];
			counter++;
			textLenght++;
		}
		Text[textLenght + 1] = '\0';
	}*/
}

void Text_ScreenElement::SetIntText(int dnum, uint8_t lenght, char fchar)
{
	char dstr[lenght];
	
	uint16_t udint = dnum;
	uint16_t rsigns = 0;
	
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
				if (textLenght < MaxLenght - 1)
				{
					Text[textLenght] = fchar;
					textLenght++;
				}
				else
					break;
			}
		}
		
		for (uint8_t i = 0; i < rsigns; i++)
		{
			if (textLenght < MaxLenght - 1)
			{
				Text[textLenght] = dstr[i];
				textLenght++;
			}
			else
				break;
		}
		Text[textLenght + 1] = '\0';
	}
	else
	{
		for (uint8_t i = 0; i < lenght - 1; i++)
		{
			if (textLenght < MaxLenght - 1)
			{
				Text[textLenght] = fchar;	
				textLenght++;
			}
			else
				break;
		}
		
		if (textLenght < MaxLenght - 1)
		{
			Text[textLenght] = '0';	
			textLenght++;
		}
			
		Text[textLenght + 1] = '\0';
	}

}

void Text_ScreenElement::SetIntText(int dnum, uint8_t lenght)
{
	SetIntText(dnum, lenght, ' ');
}

void Text_ScreenElement::FillEndBySpaces()
{
	for (uint8_t i = textLenght; i < MaxLenght - 1; i++)
	{
		Text[textLenght] = ' ';	
		textLenght++;
	}
	Text[textLenght] = '\0';
}

Rect_ScreenElement::Rect_ScreenElement(uint8_t left_x, 
	uint8_t top_y, 
	uint8_t right_x, 
	uint8_t bottom_y, 
	screenStyle * mainStyle,
	screenStyle * selectedStyle)
	: BaseScreenElement(left_x, top_y,right_x,bottom_y,mainStyle, selectedStyle)
{
}

Rect_ScreenElement::~Rect_ScreenElement(){}

void Rect_ScreenElement::Render()
{
		if (selected)
			LCD_DrawRectangle(Left_X, Top_Y, Right_X, Bottom_Y, SelectedStyle->foreColor);
		else
			LCD_DrawRectangle(Left_X, Top_Y, Right_X, Bottom_Y, MainStyle->foreColor);
}


bool BaseScreenElement::_getUpdated()
{
	return updated;
}

void BaseScreenElement::_setUpdated(bool Updated)
{
	updated = Updated;
}



