#ifndef __SCREENOBJECTSEXT__H
#define __SCREENOBJECTSEXT__H


#include "ScreenElement.hpp"
#include <vector>

extern Text_ScreenElement Date_FirstPart;
extern Text_ScreenElement Date_SecondPart;
extern Text_ScreenElement Time;
extern Text_ScreenElement Buttom_Left;
extern Text_ScreenElement Buttom_Right;

extern std::vector<BaseScreenElement*> TopBottom_FirstScreen;
extern std::vector<BaseScreenElement*> TopBottom_SecondScreen; 
extern std::vector<std::vector<BaseScreenElement*>> TopBottom_Screens;

//info screen 
extern Text_ScreenElement Info_Header;
extern Rect_ScreenElement Info_Header_Border;
extern Text_ScreenElement Info_SubHeader;
extern Text_ScreenElement Info_FirstString;
extern Text_ScreenElement Info_SecondString;
extern Text_ScreenElement Info_ThirdString;
extern Text_ScreenElement Info_FourthString;

extern std::vector<BaseScreenElement*> Info_Screen;
extern std::vector<std::vector<BaseScreenElement*>> Info_Screens;

//menu screen
extern Text_ScreenElement Menu_Header;
extern Text_ScreenElement Menu_SubHeader;
extern Text_ScreenElement Menu_PrevString;
extern Text_ScreenElement Menu_CurrentString;
extern Rect_ScreenElement Menu_CurrentScreen_Border;
extern Text_ScreenElement Menu_NextString;
extern std::vector<BaseScreenElement*> Menu_Screen;
extern std::vector<BaseScreenElement*> Menu_Screen_Selected; 

void getRectCoordinates(std::vector<BaseScreenElement*> &screen, uint8_t &left_x, uint8_t &top_y, uint8_t &right_x, uint8_t &bottom_y);

extern char prefixStr[16];

#endif