#include "MenuElement.hpp"
#include "Auxiliary.h"
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

MenuElement::MenuElement( 
	MenuElementBase* parentItem, 
	MenuElementBase* prevInListItem, 
	std::string name)
	: MenuElementBase(name,
	parentItem, 
	prevInListItem)
{
	MenuElementTypeIndex = MENU_ELEMENT_TYPE_INDEX;
}

MenuElement::MenuElement(MenuElementBase* parentItem, 
	MenuElementBase* prevInListItem, 
	std::string name, 
	IntParamItemLPfnc downLongPressFnc)
	:MenuElementBase(name,
	parentItem, 
	prevInListItem)
{
	MenuElementTypeIndex = MENU_ELEMENT_TYPE_INDEX;
}

MenuElement::MenuElement( 
	MenuElementBase* parentItem, 
	MenuElementBase* prevInListItem, 
	std::string name,
	uint16_t parametr, 
	intTune* tune)
	: MenuElementBase(name,
	parentItem, 
	prevInListItem)
	, Tune(tune)
	, Parametr(parametr)
{
	MenuElementTypeIndex = MENU_ELEMENT_TYPE_INDEX;

}

MenuElement::MenuElement(
	MenuElementBase* parentItem, 
	MenuElementBase* prevInListItem, 
	std::string name, 
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
	MenuElementTypeIndex = MENU_ELEMENT_TYPE_INDEX;
}


void MenuElement::saveParametr()
{
	Tune->_setVal(Parametr) ;
	Tune->save();
}

void MenuElement::invokeDownLongPress()
{
	if (Tune != nullptr)
	saveParametr();
	if (DownLongPressFnc != nullptr)
	DownLongPressFnc(Parametr);
}

MenuElementIntSelector::MenuElementIntSelector(MenuElementBase* parentItem, 
	MenuElementBase* prevInListItem, 
	std::string name, 
	uint16_t initVal, 
	uint16_t minVal, 
	uint16_t maxVal, 
	uint16_t step, 
	intTune* tune)
	: MenuElementBase(name,
	parentItem, 
	prevInListItem)
{
	MenuElementTypeIndex = INT_SELECTOR_MENU_ELEMENT_TYPE_INDEX;
}

MenuElementIntSelector::MenuElementIntSelector(MenuElementBase* parentItem, 
	MenuElementBase* prevInListItem, 
	std::string name, 
	uint16_t initVal, 
	uint16_t minVal, 
	uint16_t maxVal, 
	uint16_t step, 
	intTune* tune, 
	IntParamItemLPfnc downLongPressFnc)
	: MenuElementBase(name,
	parentItem, 
	prevInListItem)
{
	MenuElementTypeIndex = INT_SELECTOR_MENU_ELEMENT_TYPE_INDEX;
}

void MenuElementBase::fillTextScreenElement(Text_ScreenElement* element)
{
	element->SetText(Name, true);
	element->selected = selected;
}
