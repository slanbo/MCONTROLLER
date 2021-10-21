#include "MenuElement.hpp"
#include "Auxiliary.h"
#include "ScreenObjects.hpp"
#include "string.h"


//base
MenuElementBase::MenuElementBase(std::string name,
	MenuElementBase* parentItem, 
	MenuElementBase* prevInListItem)
	: ParentItem(parentItem)
	, PrevInListItem(prevInListItem)	
{
	for (uint8_t i = 0; i < NAME_LENGHT; i++)
	{
		if (name.c_str()[i] != 0)
			Name[i] = name.c_str()[i];
	}
}

MenuElementBase::MenuElementBase(std::string name,
	MenuElementBase* parentItem, 
	MenuElementBase* prevInListItem,
	BaseItemLPfnc downLongPressFnc)
	: ParentItem(parentItem)
	, PrevInListItem(prevInListItem)
	, DownLongPressFnc(downLongPressFnc)
{
	for (uint8_t i = 0; i < NAME_LENGHT; i++)
	{
		if (name.c_str()[i] != 0)
			Name[i] = name.c_str()[i];
	}
}

void MenuElementBase::FillScreen()
{
	char str[MAX_CHARS_IN_SCREEN * 2] = { 0 };
	
	Menu_Header.SetText("Меню настроек:", 16);
	
	// sub menu header
	if(ParentItem == nullptr)
		strcpy(str, "Корень меню:");
	else
	{
		strcpy(str, ParentItem->Name);
	}
	Menu_SubHeader.SetText(str, 16);
	Menu_PrevString.SetText(PrevItem->Name, 16);
	Menu_CurrentString.SetText(Name, 16);
	Menu_NextString.SetText(NextItem->Name, 16);
	
}

MenuElementBase* MenuElementBase::GetPrevItem()
{
	return PrevItem;
}

MenuElementBase* MenuElementBase::GetNextItem()
{
	return NextItem;
}

void MenuElementBase::invokeDownLongPress()
{
	DownLongPressFnc();
}
//Menu element

MenuElement::MenuElement(std::string name, 
	MenuElementBase* parentItem, 
	MenuElementBase* prevInListItem, 
	uint16_t parametr, 
	intTune* tune)
	: MenuElementBase(name,
	parentItem, 
	prevInListItem)
	, Tune(tune)
	, Parametr(parametr)
{
}

MenuElement::MenuElement(std::string name, 
	MenuElementBase* parentItem, 
	MenuElementBase* prevInListItem, 
	IntParamItemLPfnc downLongPressFnc, 
	uint16_t parametr, 
	intTune* tune)
	: MenuElementBase(name,
	parentItem, 
	prevInListItem)
	, Tune(tune)
	, Parametr(parametr)
	, DownLongPressFnc(downLongPressFnc)
{
}


void MenuElement::saveParametr()
{
	Tune->val = Parametr;
	Tune->save();
}

void MenuElement::invokeDownLongPress()
{
	saveParametr();
	DownLongPressFnc(Parametr);
}