#include "Buttons.hpp"
#include "MenuClass.hpp"

extern Menu* mainMenu;

void leftButton_Short_Press::processButtonPress()
{
	mainMenu->moveCurrentToPrev();
}

void rightButton_Short_Press::processButtonPress()
{
	mainMenu->moveCurrentToNext();
}

void leftButton_Long_Press::processButtonPress()
{
	mainMenu->moveCurrentToParent();
}

void leftButton_Long_Long_Press::processButtonPress()
{
}

void rightButton_Long_Press::processButtonPress()
{
	mainMenu->CurrentItemBase->invokeDownLongPress();
	mainMenu->moveCurrentToChild();
}

void rightButton_Long_Long_Press::processButtonPress()
{
	
}


void bothButtons_Short_Press::processButtonPress()
{
	
}


//BUTTONS

double ticksKey1Pressed = 0;
double ticksKey2Pressed = 0;

leftButton_Short_Press LeftButton_Short_Press("lbsp");
rightButton_Short_Press RightButton_Short_Press("rbsp");
leftButton_Long_Press LeftButton_Long_Press("lblp");
leftButton_Long_Long_Press LeftButton_Long_Long_Press("lbllp");
rightButton_Long_Press RightButton_Long_Press("rblp");
rightButton_Long_Long_Press RightButton_Long_Long_Press("rbllp");
bothButtons_Short_Press BothButtons_Short_Press("bbsp");
	
