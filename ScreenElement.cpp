#include "ScreenElement.hpp"
#include "GUI.h"
#include "utf8_to_cp1251.h" 
#include "Auxiliary.h"

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

Text_ScreenElement::~Text_ScreenElement()
{
}

void Text_ScreenElement::Render()
{
	screenStyle* currentStyle = MainStyle;
	if (selected)
		currentStyle = SelectedStyle;
	
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
	
	if (deltaLenght > 0)
		LCD_DrawFillRectangle(endxpos, Top_Y, endxpos + deltaLenght * (currentStyle->font.Size + 2), Top_Y + currentStyle->font.Size, currentStyle->backColor);
	SetRightBottomPoint(endxpos + deltaLenght * (currentStyle->font.Size + 2), Top_Y + currentStyle->font.Size);
}

void Text_ScreenElement::SetRightBottomPoint(uint8_t right_x, uint8_t bottom_y)
{
	if (right_x > Right_X)
		Right_X = right_x;
	if (bottom_y > Bottom_Y)
		Bottom_Y = bottom_y;
}

void Text_ScreenElement::SetText(std::string text, bool convertToCp1251)
{
	const char* charptr = text.c_str();
	uint8_t lenght = 0;
	textLenght = 0;
	
	if (convertToCp1251)
	{
	convertUtf8ToCp1251(charptr, Text);
	while (Text[lenght] != 0)
		lenght++;
	textLenght = lenght + 1;
	}

	else
	{
		while (charptr[lenght] != 0)
		{
			Text[lenght] = charptr[lenght];
			lenght++;
		}
		Text[lenght + 1] = '\0';
		textLenght = lenght + 1;
	}
}

void Text_ScreenElement::AddChars(const char* charptr)
{
	uint8_t lenght = 0;
	while (charptr[lenght] != 0)
		lenght++;
	
	uint8_t tlenght = 0;
	while (Text[tlenght] != 0)
		tlenght++;
	
	uint8_t i = 0;
	while (charptr[i] != 0)
		{
			Text[tlenght + i - 1] = charptr[i];
			i++;
		}
		Text[tlenght + lenght + 1] = '\0';
		textLenght = tlenght + lenght;

}


void Text_ScreenElement::AddIntStr(int dnum, uint8_t lenght)
{
	char dstr[lenght];
	
	uint16_t udint = dnum;
	uint16_t rsigns = 0;
	
	if (dnum != 0)
	{
		while (udint > 0)
		{
			udint = udint / 10;
			rsigns ++;
		}
	
		inttoabase10(dnum, dstr);
	
		uint8_t zeros = lenght - rsigns;
		for (uint8_t i = 0; i < zeros; i++)
		{
			Text[textLenght - 2 + i] = ' ';
		}
		textLenght = textLenght - 2 + zeros;
	
		for (uint8_t i = 0; i < rsigns; i++)
		{
			Text[textLenght + i] = dstr[i];
		}
		textLenght = textLenght + rsigns;
		Text[textLenght + 1] = '\0';
		textLenght++;
		textLenght++;
	}
	else
	{
		for (uint8_t i = 0; i < lenght; i++)
			Text[textLenght - 2 + i] = ' ';	
			textLenght = textLenght - 2 + lenght;
			Text[textLenght + 1] = '\0';
			textLenght++;
			textLenght++;

	}
}

void Text_ScreenElement::Set_Prefix_IntVal_Postfix_Text(std::string prefix,
	uint16_t intVal, uint8_t untValLenght, std::string postfix, bool convertToCp1251)
{
	uint8_t preflenght = 0;
	uint8_t postlenght = 0;
	
	const char* prefcharptr = prefix.c_str();
	const char* postcharptr = postfix.c_str();
	
	char buff[MAX_CHARS_IN_SCREEN * 2] = { 0 };
	
	while (prefcharptr[preflenght] != 0)
	{
		buff[preflenght] = prefcharptr[preflenght];
		preflenght++;
	}
	
	addIntStr(buff, intVal, untValLenght);	

	while (postcharptr[postlenght] != 0)
	{
		buff[preflenght + untValLenght + postlenght] = postcharptr[postlenght];
		postlenght++;
	}
	buff[preflenght + untValLenght + postlenght + 1] = '\0';
	
	uint8_t lenght = 0;
	if (convertToCp1251)
	{
		convertUtf8ToCp1251(buff, Text);
		while (Text[lenght] != 0)
			lenght++;
		textLenght = lenght + 1;
	}
	else
		{
			while (buff[lenght] != 0)
			{
				Text[lenght] = buff[lenght];
				lenght++;
			}
		Text[lenght + 1] = '\0';
		textLenght = lenght + 2;
		}
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











