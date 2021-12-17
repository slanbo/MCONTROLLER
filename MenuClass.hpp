#ifndef __MENUCLASS__H
#define __MENUCLASS__H

#include "MenuElement.hpp"

#define MENU_HEADER_BOARD_GAP 2
#define MENU_ELEMENT_BOARD_GAP 2

class MenuBase
{
public:
	MenuBase();
	~MenuBase();
	
	virtual void moveCurrentToChild() = 0;
	virtual void moveCurrentToParent() = 0;
	virtual void moveCurrentToPrev() = 0;
	virtual void moveCurrentToNext() = 0;
	virtual void FillScreen() = 0;
	virtual void clearLCD() = 0;
	virtual void init(uint8_t index);
	
	uint8_t Index = 0;
	
	
protected:
	
	uint8_t Left_X = 0;
	uint8_t Top_Y = 0;
	uint8_t Right_X = 0;
	uint8_t Bottom_Y = 0;
	uint16_t BackColor = 0;
	
};

class Menu : MenuBase
{
public:
	
	Menu(MenuElementBase* currentItem);
	
	virtual void moveCurrentToChild();
	virtual void moveCurrentToParent();
	virtual void moveCurrentToPrev();
	virtual void moveCurrentToNext();
	virtual void FillScreen();
	virtual void clearLCD();
	
	MenuElementBase* CurrentItemBase;
	MenuElementBase* SelectedItemBase;

private:
	
};


#endif 