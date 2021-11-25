#include "MenuClass.hpp"
#include "string.h"
#include "utf8_to_cp1251.h"
#include "Lcd_Driver.h"
#include "GUI.h"
#include "TuneObjectsExt.hpp"
#include "ScreenObjectsExt.hpp"

Menu::Menu(MenuElementBase* currentItem)
	: CurrentItemBase(currentItem)
{
}
;

void Menu::moveCurrentToChild()
{
	if (CurrentItemBase->ChildItem != nullptr)
	{
		CurrentItemBase = CurrentItemBase->ChildItem;
		
	}	
	else
	{
		if (!CurrentItemBase->selected)
			CurrentItemBase->selected = true;
		else
			CurrentItemBase->selected = false;
	}
}

void Menu::moveCurrentToParent()
{
	CurrentItemBase->selected = false;
	if (CurrentItemBase->ParentItem != nullptr)
	{
		CurrentItemBase = CurrentItemBase->ParentItem;
	}
}


void Menu::moveCurrentToPrev()
{
	CurrentItemBase->selected = false;
	CurrentItemBase = CurrentItemBase->GetPrevItem();
}


void Menu::moveCurrentToNext()
{
	CurrentItemBase->selected = false;
	CurrentItemBase = CurrentItemBase->GetNextItem();
}

void Menu::FillScreen()
{
	char str[MAX_CHARS_IN_SCREEN * 2] = { 0 };
	
	Menu_Header->SetText("Меню настроек:", true);
	
	// sub menu header
	if(CurrentItemBase->ParentItem == nullptr)
		strcpy(str, "Корень меню:");
	else
	{
		if (CurrentItemBase->MenuElementTypeIndex == MENU_ELEMENT_TYPE_INDEX)
			strcpy(str, CurrentItemBase->ParentItem->Name);
		else if(CurrentItemBase->MenuElementTypeIndex == INT_SELECTOR_MENU_ELEMENT_TYPE_INDEX)
			strcpy(str, CurrentItemBase->Name);
		else
			strcpy(str, CurrentItemBase->Name);
	}
	Menu_SubHeader->SetText(str, true);
	
	switch (CurrentItemBase->MenuElementTypeIndex)
	{
	case MENU_ELEMENT_TYPE_INDEX:
		{
			MenuElement* CurrentItem = (MenuElement*)CurrentItemBase;
			CurrentItem->fillTextScreenElement(Menu_CurrentString);
			break;
		}
	case INT_SELECTOR_MENU_ELEMENT_TYPE_INDEX:
		{
			MenuElementIntSelector* CurrentItem = (MenuElementIntSelector*)CurrentItemBase;
			CurrentItem->fillTextScreenElement(Menu_CurrentString);
			break;
		}
	default:
		{
			MenuElement* CurrentItem = (MenuElement*)CurrentItemBase;
			break;
		}
	}
	
		
	switch (CurrentItemBase->PrevItem->MenuElementTypeIndex)
	{
	case MENU_ELEMENT_TYPE_INDEX:
		{
			MenuElement* PrevItem = (MenuElement*)CurrentItemBase->PrevItem;
			PrevItem->fillTextScreenElement(Menu_PrevString);
			break;
		}
	case INT_SELECTOR_MENU_ELEMENT_TYPE_INDEX:
		{
			MenuElementIntSelector* PrevItem = (MenuElementIntSelector*)CurrentItemBase->PrevItem;
			PrevItem->fillTextScreenElement(Menu_PrevString);
			break;
		}
	default:
		{
			MenuElement* PrevItem = (MenuElement*)CurrentItemBase->PrevItem;
			PrevItem->fillTextScreenElement(Menu_PrevString);
			break;
		}
	}		
		
	switch (CurrentItemBase->NextItem->MenuElementTypeIndex)
	{
	case MENU_ELEMENT_TYPE_INDEX:
		{
			MenuElement* NextItem = (MenuElement*)CurrentItemBase->NextItem;
			NextItem->fillTextScreenElement(Menu_NextString);
			break;
		}
	case INT_SELECTOR_MENU_ELEMENT_TYPE_INDEX:
		{
			MenuElementIntSelector* NextItem = (MenuElementIntSelector*)CurrentItemBase->NextItem;
			NextItem->fillTextScreenElement(Menu_NextString);
			break;
		}
	default:
		{
			MenuElement* NextItem = (MenuElement*)CurrentItemBase->NextItem;
			NextItem->fillTextScreenElement(Menu_NextString);
			break;
		}
	}		
	
	getRectCoordinates(Menu_Screen, Left_X, Top_Y, Right_X, Bottom_Y);
	
}


void Menu::clearLCD()
{
	LCD_DrawFillRectangle(Left_X,
		Top_Y,
		Right_X,
		Bottom_Y,
		BackColor);
}




void MenuBase::init(uint8_t index)
{
	Index = index;
}


MenuBase::~MenuBase()
{
}


MenuBase::MenuBase()
{
}
