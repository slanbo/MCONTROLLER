//#ifndef __SCREENOBJECTS__H
//#define __SCREENOBJECTS__H

#include "ScreenElement.hpp"
#include "Lcd_Driver.h"
#include <vector>
#include "LCDFonts.hpp"


#define VERTICAL_SCREEN_SIZE 130
#define HORIZONTAL_SCREEN_SIZE 130
#define LETTER_WIDTH 7

#define SCREEN_GAP 2
#define STRINGS_GAP 4
#define BORDER_GAP 1

screenStyle GRAY0_BLACK_VERANDA12 = { GRAY0, BLACK, Verdana12x12 };
screenStyle GREEN_BLACK_VERANDA12 = { GREEN, BLACK, Verdana12x12 };
screenStyle YELLOW_BLACK_VERANDA12 = { YELLOW, BLACK, Verdana12x12 };
screenStyle RED_BLACK_VERANDA12 = { RED, BLACK, Verdana12x12 };


//top bottom screen

Text_ScreenElement* Date_FirstPart = new Text_ScreenElement(SCREEN_GAP,
	SCREEN_GAP,
	&GRAY0_BLACK_VERANDA12, &GREEN_BLACK_VERANDA12, 12);

Text_ScreenElement* Time = new Text_ScreenElement(HORIZONTAL_SCREEN_SIZE - SCREEN_GAP - 47,
	SCREEN_GAP,
	&GREEN_BLACK_VERANDA12,
	&GRAY0_BLACK_VERANDA12,
	9);
Text_ScreenElement* Buttom_Left = new Text_ScreenElement(SCREEN_GAP,
	VERTICAL_SCREEN_SIZE - SCREEN_GAP - Verdana12x12.Size,
	&YELLOW_BLACK_VERANDA12,
	&GRAY0_BLACK_VERANDA12,
	6);
Text_ScreenElement* Buttom_Right = new Text_ScreenElement(HORIZONTAL_SCREEN_SIZE - SCREEN_GAP - 30,
	VERTICAL_SCREEN_SIZE - SCREEN_GAP - Verdana12x12.Size,
	&YELLOW_BLACK_VERANDA12,
	&GRAY0_BLACK_VERANDA12,
	6);

std::vector<BaseScreenElement*> TopBottom_FirstScreen = { Date_FirstPart, Time, Buttom_Left, Buttom_Right };
std::vector<std::vector<BaseScreenElement*>> TopBottom_Screens = { TopBottom_FirstScreen };

//info screen 
Text_ScreenElement* Info_Header = new Text_ScreenElement(
	SCREEN_GAP,
	SCREEN_GAP + (Verdana12x12.Size + STRINGS_GAP),
	&YELLOW_BLACK_VERANDA12,
	&YELLOW_BLACK_VERANDA12,
	16);

Rect_ScreenElement* Info_Header_Border = new  Rect_ScreenElement(
	SCREEN_GAP - BORDER_GAP,
	SCREEN_GAP + (Verdana12x12.Size + STRINGS_GAP) - BORDER_GAP,
	HORIZONTAL_SCREEN_SIZE - SCREEN_GAP + BORDER_GAP,
	SCREEN_GAP + Verdana12x12.Size * 2 + STRINGS_GAP,
	&YELLOW_BLACK_VERANDA12,
	&YELLOW_BLACK_VERANDA12);
Text_ScreenElement* Info_SubHeader = new Text_ScreenElement(SCREEN_GAP,
	SCREEN_GAP + (Verdana12x12.Size + STRINGS_GAP) * 2,
	&GREEN_BLACK_VERANDA12, &GREEN_BLACK_VERANDA12,	16);
Text_ScreenElement* Info_FirstString = new Text_ScreenElement(SCREEN_GAP,
	SCREEN_GAP + (Verdana12x12.Size + STRINGS_GAP) * 3,
	&GRAY0_BLACK_VERANDA12, &YELLOW_BLACK_VERANDA12, 16);
Text_ScreenElement* Info_SecondString = new Text_ScreenElement(SCREEN_GAP,
	SCREEN_GAP + (Verdana12x12.Size + STRINGS_GAP) * 4,
	&GRAY0_BLACK_VERANDA12, &YELLOW_BLACK_VERANDA12, 16);
Text_ScreenElement* Info_ThirdString = new Text_ScreenElement(SCREEN_GAP,
	SCREEN_GAP + (Verdana12x12.Size + STRINGS_GAP) * 5,
	&GRAY0_BLACK_VERANDA12, &YELLOW_BLACK_VERANDA12, 16);
Text_ScreenElement* Info_FourthString = new Text_ScreenElement(SCREEN_GAP,
	SCREEN_GAP + (Verdana12x12.Size + STRINGS_GAP) * 6,
	&GRAY0_BLACK_VERANDA12, &YELLOW_BLACK_VERANDA12, 16);


std::vector<BaseScreenElement*> Info_Screen = { 
	Info_Header,
	Info_Header_Border,
	Info_SubHeader,
	Info_FirstString,
	Info_SecondString,
	Info_ThirdString,
	Info_FourthString
};

std::vector<std::vector<BaseScreenElement*>> Info_Screens = { Info_Screen };

//menu screen
Text_ScreenElement* Menu_Header = new Text_ScreenElement(
	SCREEN_GAP,
	SCREEN_GAP + (Verdana12x12.Size + STRINGS_GAP),
	&YELLOW_BLACK_VERANDA12,
	&YELLOW_BLACK_VERANDA12,
	16);
Text_ScreenElement* Menu_SubHeader = new Text_ScreenElement(
	SCREEN_GAP,
	SCREEN_GAP + (Verdana12x12.Size + STRINGS_GAP) * 2,
	&GREEN_BLACK_VERANDA12,
	&GREEN_BLACK_VERANDA12,
	16);
Text_ScreenElement* Menu_PrevString = new Text_ScreenElement(SCREEN_GAP,
	SCREEN_GAP + (Verdana12x12.Size + STRINGS_GAP) * 3,
	&GRAY0_BLACK_VERANDA12,
	&YELLOW_BLACK_VERANDA12,
	16);
Text_ScreenElement* Menu_CurrentString = new Text_ScreenElement(SCREEN_GAP,
	SCREEN_GAP + (Verdana12x12.Size + STRINGS_GAP) * 4,
	&GRAY0_BLACK_VERANDA12,
	&YELLOW_BLACK_VERANDA12,
	14);
Rect_ScreenElement* Menu_CurrentScreen_Border = new Rect_ScreenElement(
	SCREEN_GAP - BORDER_GAP,
	SCREEN_GAP + (Verdana12x12.Size + STRINGS_GAP) * 4 - BORDER_GAP,
	HORIZONTAL_SCREEN_SIZE - SCREEN_GAP + BORDER_GAP,
	SCREEN_GAP + (Verdana12x12.Size + STRINGS_GAP) * 4 + Verdana12x12.Size + BORDER_GAP,
	&GREEN_BLACK_VERANDA12,
	&RED_BLACK_VERANDA12);
Text_ScreenElement* Menu_NextString = new Text_ScreenElement(SCREEN_GAP,
	SCREEN_GAP + (Verdana12x12.Size + STRINGS_GAP) * 5,
	&GRAY0_BLACK_VERANDA12,
	&YELLOW_BLACK_VERANDA12,
	16);
Rect_ScreenElement* Menu_Header_Border = new Rect_ScreenElement(
	SCREEN_GAP - BORDER_GAP,
	SCREEN_GAP + (Verdana12x12.Size + STRINGS_GAP) - BORDER_GAP,
	HORIZONTAL_SCREEN_SIZE - SCREEN_GAP + BORDER_GAP,
	SCREEN_GAP + Verdana12x12.Size * 2 + STRINGS_GAP,
	&YELLOW_BLACK_VERANDA12,
	&YELLOW_BLACK_VERANDA12);

std::vector<BaseScreenElement*> Menu_Screen = {
	Menu_Header,
	Menu_SubHeader,
	Menu_PrevString,
	Menu_CurrentString,
	Menu_NextString,
	Menu_CurrentScreen_Border,
	Menu_Header_Border
		
};

void getRectCoordinates(std::vector<BaseScreenElement*> &screen, uint8_t &left_x, uint8_t &top_y, uint8_t &right_x, uint8_t &bottom_y)
{
	for (auto scrElement : screen)
	{
		if (scrElement->Left_X < left_x)
			left_x = scrElement->Left_X;
		if (scrElement->Top_Y < top_y)
			top_y = scrElement->Top_Y;
		if (scrElement->Right_X > right_x)
			right_x = scrElement->Right_X;
		if (scrElement->Bottom_Y > bottom_y)
			bottom_y = scrElement->Bottom_Y;
	}
	
}

char prefixStr[16];

//#endif
