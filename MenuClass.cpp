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
		
		MenuElementBase* currItem = CurrentItemBase;
		while(currItem != nullptr)
		{
			currItem = currItem->NextInListItem;
			if (currItem->ParentItem == CurrentItemBase->ParentItem)
			{
				MenuElement* me = (MenuElement*)currItem;
				if (me->Tune != nullptr)
					if (me->Tune->_getVal() == me->Parametr)
					{
						CurrentItemBase = (MenuElementBase*)me;
						break;
					}
				
			}
			
		}
			
		
		
		
	}	
	else
	{
		if (CurrentItemBase != SelectedItemBase)
			SelectedItemBase = CurrentItemBase;
		else
			SelectedItemBase = nullptr;
		
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
	char str[FONT_12_MAX_SIMVOLS_IN_STRING * 2] = { 0 };
	
	Menu_Header->ClearText();
	Menu_Header->SetChars("Меню настроек:", true);
	Menu_Header->_setUpdated(true);
	
	// sub menu header
	Menu_SubHeader->ClearText();
	if(CurrentItemBase->ParentItem == nullptr)
		Menu_SubHeader->SetChars("Корень меню:", true);
	else
	{
		if (CurrentItemBase->MenuElementTypeIndex == MENU_ELEMENT_TYPE_INDEX)
			Menu_SubHeader->SetChars(CurrentItemBase->ParentItem->Name, false);
		else if(CurrentItemBase->MenuElementTypeIndex == INT_SELECTOR_MENU_ELEMENT_TYPE_INDEX)
			Menu_SubHeader->SetChars(CurrentItemBase->Name, false);
		else
			Menu_SubHeader->SetChars(CurrentItemBase->Name, false);
	}
	Menu_SubHeader->FillEndBySpaces();
	Menu_SubHeader->_setUpdated(true);
	
	switch (CurrentItemBase->MenuElementTypeIndex)
	{
	case MENU_ELEMENT_TYPE_INDEX:
		{
			MenuElement* CurrentItem = (MenuElement*)CurrentItemBase;
			CurrentItem->fillTextScreenElement(Menu_CurrentString);
			if (CurrentItemBase == SelectedItemBase)
				Menu_CurrentString->marked = true;
			else
				Menu_CurrentString->marked = false;
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
			break;
		}
	default:
		{
			MenuElement* NextItem = (MenuElement*)CurrentItemBase->NextItem;
			NextItem->fillTextScreenElement(Menu_NextString);
			break;
		}
	}		
	
	switch (CurrentItemBase->NextItem->NextItem->MenuElementTypeIndex)
	{
	case MENU_ELEMENT_TYPE_INDEX:
		{
			MenuElement* NextItem = (MenuElement*)CurrentItemBase->NextItem->NextItem;
			NextItem->fillTextScreenElement(Menu_NextNextString);
			break;
		}
	case INT_SELECTOR_MENU_ELEMENT_TYPE_INDEX:
		{
			break;
		}
	default:
		{
			MenuElement* NextItem = (MenuElement*)CurrentItemBase->NextItem->NextItem;
			NextItem->fillTextScreenElement(Menu_NextNextString);
			break;
		}
	}		
	
	getRectCoordinates(Menu_Screen, Left_X, Top_Y, Right_X, Bottom_Y);
	
}


void Menu::clearLCD()
{
	LCD_DrawFillRectangle(1,
		1,
		129,
		129,
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
