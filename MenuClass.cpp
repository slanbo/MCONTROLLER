#include "MenuClass.hpp"
#include "string.h"
#include "utf8_to_cp1251.h"
#include "Lcd_Driver.h"
#include "GUI.h"
#include "TuneObjectsExt.hpp"
#include "ScreenObjectsExt.hpp"

Menu::Menu(MenuElement* currentItem)
	: CurrentItem(currentItem)
{
}
;

void Menu::moveCurrentToChild()
{
	if (CurrentItem->ChildItem != nullptr)
	{
		MenuElement* arrow = CurrentItem->ChildItem;
		MenuElement* cursor = CurrentItem->ChildItem;
	
		if (arrow->Tune != nullptr) 
		{
			if (arrow->MaxIntParametr == 0xffff & arrow->MinIntParametr == 0xffff)
			{
				do 
				{	
					if (cursor->Tune->val == cursor->IntParametr) 
					{
						break;
					}
					cursor = cursor->GetNextItem();
				} while (cursor != arrow);
			}
			else
			{
				cursor->Tune->restore();
				cursor->IntParametr = cursor->Tune->val;
				cursor->GetPrevIntParametr();
				cursor->GetNextIntParametr();
			}
		}	
		CurrentItem = cursor;
	}
	else
	{
		if (!CurrentItem->selected)
			CurrentItem->selected = true;
		else
			CurrentItem->selected = false;
	}
}

void Menu::moveCurrentToParent()
{
	CurrentItem->selected = false;
	if (CurrentItem->ParentItem != nullptr)
	{
		CurrentItem = CurrentItem->ParentItem;
	}
}


void Menu::moveCurrentToPrev()
{
	CurrentItem->selected = false;
	CurrentItem = CurrentItem->GetPrevItem();
}


void Menu::moveCurrentToNext()
{
	CurrentItem->selected = false;
	CurrentItem = CurrentItem->GetNextItem();
}

void Menu::FillScreen()
{
	char str[MAX_CHARS_IN_SCREEN * 2] = { 0 };
	
	Menu_Header.SetText("Меню настроек:", 16);
	
	// sub menu header
	if(CurrentItem->ParentItem == nullptr)
		strcpy(str, "Корень меню:");
	else
	{
		if (CurrentItem->MaxIntParametr == 0xffff & CurrentItem->MinIntParametr == 0xffff)
			strcpy(str, CurrentItem->ParentItem->Name);
		else
			strcpy(str, CurrentItem->Name);
	}
	Menu_SubHeader.SetText(str, 16);
	
	if (CurrentItem->MinIntParametr != 0xffff & CurrentItem->MaxIntParametr != 0xffff)
	{
		Menu_PrevString.selected = CurrentItem->prevIntParametr != CurrentItem->Tune->val;
		Menu_CurrentString.selected = CurrentItem->IntParametr != CurrentItem->Tune->val;
		Menu_NextString.selected = CurrentItem->nextIntParametr != CurrentItem->Tune->val;
	}
	else
	{
		Menu_PrevString.selected =  CurrentItem->PrevItem->Tune!=nullptr & CurrentItem->PrevItem->Tune->val != CurrentItem->PrevItem->IntParametr;
		Menu_CurrentString.selected = CurrentItem->Tune != nullptr & CurrentItem->Tune->val != CurrentItem->IntParametr;
		Menu_NextString.selected =  CurrentItem->NextItem->Tune != nullptr & CurrentItem->NextItem->Tune->val != CurrentItem->NextItem->IntParametr;
	}
	CurrentItem->GetPrevItemName(str);
	Menu_PrevString.SetText(str, 16);
	
	CurrentItem->GetCurrItemName(str);
	Menu_CurrentString.SetText(str, 16);
	Menu_CurrentScreen_Border.selected = CurrentItem->selected;
	
	CurrentItem->GetNextItemName(str);
	Menu_NextString.SetText(str, 16);
	
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
