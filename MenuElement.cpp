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
	
	Menu_Header->SetText("Меню настроек:", 16);
	
	// sub menu header
	if(ParentItem == nullptr)
		strcpy(str, "Корень меню:");
	else
	{
		strcpy(str, ParentItem->Name);
	}
	Menu_SubHeader->SetText(str, 16);
	Menu_PrevString->SetText(PrevItem->Name, 16);
	Menu_CurrentString->SetText(Name, 16);
	Menu_NextString->SetText(NextItem->Name, 16);
	
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
	: MenuElement(parentItem, prevInListItem, name)
	, InitVal(initVal)
	, MinVal(minVal)
	, MaxVal(maxVal)
	, Step(step) 
	
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
	: MenuElement(parentItem, prevInListItem, name, downLongPressFnc, 0, tune),
	InitVal(initVal), 
	MinVal(minVal), 
	MaxVal(maxVal), 
	Step(step) 
{
	MenuElementTypeIndex = INT_SELECTOR_MENU_ELEMENT_TYPE_INDEX;
}

void MenuElementBase::fillTextScreenElement(Text_ScreenElement* element)
{
	element->SetText(Name, true);
	element->selected = selected;
}


void MenuElement::fillTextScreenElement(Text_ScreenElement* element)
{
	element->SetText(Name, true);
	if (Tune != nullptr)
	{
		if (Tune->_getVal() == Parametr)
			element->selected = true;
		else
			element->selected = false;		
	}
	else
		element->selected = false;		
}

void MenuElementIntSelector::fillTextScreenElement(Text_ScreenElement* element)
{
	Menu_PrevString->ClearText();
	Menu_CurrentString->ClearText();
	Menu_NextString->ClearText();
	
	if (Parametr - Step >= MinVal) 
		Menu_PrevString->SetIntText(Parametr - Step, 3);
	else
		Menu_PrevString->SetIntText(MaxVal, 3);
	
	Menu_CurrentString->SetIntText(Parametr, 3);
	
	if (Parametr + Step <= MaxVal) 
		Menu_NextString->SetIntText(Parametr + Step, 3);
	else
		Menu_NextString->SetIntText(MinVal, 3);
}

MenuElementBase* MenuElementIntSelector::GetPrevItem()
{
		if (Parametr - Step >= MinVal) 
			Parametr = 	Parametr - Step;
		else
			Parametr = 	MaxVal;
		return this;
}


MenuElementBase* MenuElementIntSelector::GetNextItem()
{
	
		if (Parametr + Step <= MaxVal) 
			Parametr = Parametr + Step;
		else
			Parametr = MinVal;
	
	return (MenuElementBase*)this;
}
