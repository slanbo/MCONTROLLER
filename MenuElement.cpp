#include "MenuElement.hpp"
#include "Auxiliary.hpp"


//base
MenuElementBase::MenuElementBase(const char* name,
	MenuElementBase* parentItem, 
	MenuElementBase* prevInListItem)
	: BaseObject(name)
	, ParentItem(parentItem)
	, PrevInListItem(prevInListItem)	
{
}

MenuElementBase::MenuElementBase(const char* name,
	MenuElementBase* parentItem, 
	MenuElementBase* prevInListItem,
	BaseItemLPfnc downLongPressFnc)
	: BaseObject(name)
	, ParentItem(parentItem)
	, PrevInListItem(prevInListItem)
	, DownLongPressFnc(downLongPressFnc)
{
	
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

void MenuElementBase::FillScreen()
{
	/*char str[MAX_CHARS_IN_SCREEN * 2] = { 0 };
	
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
	Menu_NextString->SetText(NextItem->Name, 16);*/
	
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
}

void MenuElementBase::invokeOnSelect()
{
}

//Menu element

MenuElement::MenuElement( 
	MenuElementBase* parentItem, 
	MenuElementBase* prevInListItem, 
	const char* name)
	: MenuElementBase(name,
	parentItem, 
	prevInListItem)
{
	MenuElementTypeIndex = MENU_ELEMENT_TYPE_INDEX;
}

MenuElement::MenuElement(MenuElementBase* parentItem, 
	MenuElementBase* prevInListItem, 
	const char* name, 
	IntParamfnc downLongPressFnc)
	:MenuElementBase(name,
	parentItem, 
	prevInListItem),
	DownLongPressFnc(downLongPressFnc)
{
	MenuElementTypeIndex = MENU_ELEMENT_TYPE_INDEX;
}

MenuElement::MenuElement(MenuElementBase* parentItem, 
	MenuElementBase* prevInListItem, 
	const char* name,
	uint16_t parametr, 
	IntParamfnc downLongPressFnc)
	: MenuElementBase(name,
	parentItem, 
	prevInListItem)
	, DownLongPressFnc(downLongPressFnc)
	, Parametr(parametr)	
{
	MenuElementTypeIndex = MENU_ELEMENT_TYPE_INDEX;
}

MenuElement::MenuElement(MenuElementBase* parentItem, 
	MenuElementBase* prevInListItem, 
	const char* name, 
	IntParamfnc onSelectFnc,
	IntParamfnc downLongPressFnc)
	: MenuElementBase(name,
	parentItem, 
	prevInListItem),
	OnSelectFnc(onSelectFnc),
	DownLongPressFnc(downLongPressFnc)
{
	MenuElementTypeIndex = MENU_ELEMENT_TYPE_INDEX;
}

MenuElement::MenuElement( 
	MenuElementBase* parentItem, 
	MenuElementBase* prevInListItem, 
	const char* name,
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
	const char* name,
	uint16_t parametr, 
	GetNameEndfnc addNameEndFnc)
	: MenuElementBase(name,
	parentItem, 
	prevInListItem)
	, AddNameEndFnc(addNameEndFnc)
	, Parametr(parametr)
{
	MenuElementTypeIndex = MENU_ELEMENT_TYPE_INDEX;

}


MenuElement::MenuElement(
	MenuElementBase* parentItem, 
	MenuElementBase* prevInListItem, 
	const char* name, 
	IntParamfnc downLongPressFnc, 
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

MenuElement::MenuElement(
	MenuElementBase* parentItem, 
	MenuElementBase* prevInListItem, 
	const char* name, 
	IntParamfnc onSelectFnc,
	IntParamfnc downLongPressFnc, 
	uint16_t parametr, 
	intTune* tune)
	: MenuElementBase(name,
	parentItem, 
	prevInListItem)
	, Tune(tune)
	, Parametr(parametr)
	, OnSelectFnc(onSelectFnc)
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
	DownLongPressFnc(&Parametr);
}

void MenuElement::invokeOnSelect()
{
	if (OnSelectFnc != nullptr)
		OnSelectFnc(&Parametr);
	//if (Tune != nullptr)
		//saveParametr();
		//Parametr = Tune->_getVal();
}


MenuElementIntSelector::MenuElementIntSelector(MenuElementBase* parentItem, 
	MenuElementBase* prevInListItem, 
	const char* name, 
	uint16_t initVal, 
	uint16_t minVal, 
	uint16_t maxVal, 
	uint16_t step, 
	intTune* tune)
	: MenuElement(parentItem, prevInListItem, name, 0, tune)
	, InitVal(initVal)
	, MinVal(minVal)
	, MaxVal(maxVal)
	, Step(step) 
	
{
	MenuElementTypeIndex = INT_SELECTOR_MENU_ELEMENT_TYPE_INDEX;
}

MenuElementIntSelector::MenuElementIntSelector(MenuElementBase* parentItem, 
	MenuElementBase* prevInListItem, 
	const char* name, 
	uint16_t initVal, 
	uint16_t minVal, 
	uint16_t maxVal, 
	uint16_t step, 
	intTune* tune, 
	IntParamfnc downLongPressFnc)
	: MenuElement(parentItem, prevInListItem, name, downLongPressFnc, 0, tune),
	InitVal(initVal), 
	MinVal(minVal), 
	MaxVal(maxVal), 
	Step(step) 
{
	MenuElementTypeIndex = INT_SELECTOR_MENU_ELEMENT_TYPE_INDEX;
}

MenuElementIntSelector::MenuElementIntSelector(MenuElementBase* parentItem, 
	MenuElementBase* prevInListItem, 
	const char* name, 
	uint16_t initVal, 
	uint16_t minVal, 
	uint16_t maxVal, 
	uint16_t step, 
	intTune* tune,
	IntParamfnc onSelectFnc,
	IntParamfnc downLongPressFnc)
	: MenuElement(parentItem, prevInListItem, name, onSelectFnc, downLongPressFnc, 0, tune)
	, InitVal(initVal)
	, MinVal(minVal)
	, MaxVal(maxVal)
	, Step(step) 
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
	element->ClearText();
	element->SetChars(Name, true);
	if (AddNameEndFnc != nullptr)
	{
		element->SetChars(" ", false);
		char addstr[FONT_12_MAX_SIMVOLS_IN_STRING] = { 0 };
		AddNameEndFnc(addstr, this) ;
		element->SetChars(addstr, false);
	}
		
	if (Tune != nullptr)
	{
		if (Tune->_getVal() == Parametr)
			element->selected = true;
		else
			element->selected = false;		
	}
	else
		element->selected = false;	
	
	element->FillEndBySpaces();
	element->_setUpdated(true);
}

void MenuElement::init()
{
}

void MenuElementIntSelector::fillTextScreenElement(Text_ScreenElement* element)
{
	Menu_PrevString->ClearText();
	Menu_CurrentString->ClearText();
	Menu_NextString->ClearText();
	
	Menu_PrevString->ClearText();
	if (Parametr - Step >= MinVal) 
		Menu_PrevString->SetIntText(Parametr - Step, INT_SELECTOR_BLANKS);
	else
		Menu_PrevString->SetIntText(MaxVal, INT_SELECTOR_BLANKS);
	Menu_PrevString->FillEndBySpaces();
	if (Tune != nullptr)
	{
		if (Parametr - Step <= MaxVal) 
		{
			if (Parametr - Step ==  Tune->_getVal())
				Menu_PrevString->selected = true;
			else
				Menu_PrevString->selected = false;
		}
		else
		{
			if (MaxVal ==  Tune->_getVal())
				Menu_PrevString->selected = true;
			else
				Menu_PrevString->selected = false;
		}
	}
	else
		Menu_PrevString->selected = false;
	Menu_PrevString->_setUpdated(true);
	
	Menu_CurrentString->ClearText();
	Menu_CurrentString->SetIntText(Parametr, INT_SELECTOR_BLANKS);
	Menu_CurrentString->FillEndBySpaces();
	if (Tune != nullptr)
	{
		if (Parametr ==  Tune->_getVal())
			Menu_CurrentString->selected = true;
		else
			Menu_CurrentString->selected = false;
	}
	else
		Menu_CurrentString->selected = false;
	Menu_CurrentString->_setUpdated(true);
	
	
	Menu_NextString->ClearText();
	if (Parametr + Step <= MaxVal) 
		Menu_NextString->SetIntText(Parametr + Step, INT_SELECTOR_BLANKS);
	else
		Menu_NextString->SetIntText(MinVal, INT_SELECTOR_BLANKS);
	Menu_NextString->FillEndBySpaces();
	if (Tune != nullptr)
	{
		if (Parametr + Step <= MaxVal) 
		{
			if (Parametr + Step ==  Tune->_getVal())
				Menu_NextString->selected = true;
			else
				Menu_NextString->selected = false;
		}
		else
		{
			if (MinVal ==  Tune->_getVal())
				Menu_NextString->selected = true;
			else
				Menu_NextString->selected = false;
		}
	}
	else
		Menu_NextString->selected = false;
	Menu_NextString->_setUpdated(true);
	
	Menu_NextNextString->ClearText();
	if (Parametr + Step + Step <= MaxVal) 
		Menu_NextNextString->SetIntText(Parametr + Step + Step, INT_SELECTOR_BLANKS);
	else
		Menu_NextNextString->SetIntText(MinVal, INT_SELECTOR_BLANKS);
	Menu_NextNextString->FillEndBySpaces();
	if (Tune != nullptr)
	{
		if (Parametr + Step + Step <= MaxVal) 
		{
			if (Parametr + Step + Step ==  Tune->_getVal())
				Menu_NextNextString->selected = true;
			else
				Menu_NextNextString->selected = false;
		}
		else
		{
			if (MinVal ==  Tune->_getVal())
				Menu_NextNextString->selected = true;
			else
				Menu_NextNextString->selected = false;
		}
	}
	else
		Menu_NextNextString->selected = false;
	Menu_NextNextString->_setUpdated(true);
	
}

void MenuElementIntSelector::init()
{
	Parametr = Tune->_getVal();
}
