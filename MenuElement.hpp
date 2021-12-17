#ifndef __MENUELEMENT__H
#define __MENUELEMENT__H

#include "TuneObjectsExt.hpp"
#include "ScreenObjectsExt.hpp"
#include "BaseObject.hpp"


#define NAME_LENGHT 32
#define INT_SELECTOR_BLANKS 8


using BaseItemLPfnc = bool(*)();
using IntParamfnc = bool(*)(uint16_t* param);

class MenuElementBase : public BaseObject
{
public:
	
	MenuElementBase(const char* name,
		MenuElementBase* parentItem, 
		MenuElementBase* prevInListItem);
	
	MenuElementBase(const char* name,
		MenuElementBase* parentItem, 
		MenuElementBase* prevInListItem,
		BaseItemLPfnc downLongPressFnc);
	
	//~MenuElementBase();
		
	virtual void FillScreen();
	
	virtual void invokeDownLongPress();
	virtual void invokeOnSelect();
	
	virtual MenuElementBase* GetPrevItem();
	virtual MenuElementBase* GetNextItem();	
	
	virtual void fillTextScreenElement(Text_ScreenElement* element);
	
	virtual void init() = 0;
	
	
	//char Name[NAME_LENGHT] = { 0 };
	
	BaseItemLPfnc DownLongPressFnc = nullptr;
	MenuElementBase* PrevInListItem = nullptr;
	MenuElementBase* NextInListItem = nullptr;
	MenuElementBase* ParentItem = nullptr;
	MenuElementBase* ChildItem = nullptr;
	MenuElementBase* PrevItem = nullptr;
	MenuElementBase* NextItem = nullptr;
	
	uint8_t MenuElementTypeIndex = 0;
	bool selected = false;

	
protected:
	
	
};

using GetNameEndfnc = void(*)(char*, MenuElementBase*);

class MenuElement : public MenuElementBase
{
public:
	
	MenuElement(
		MenuElementBase* parentItem, 
		MenuElementBase* prevInListItem,
		const char* name
		);
	
	MenuElement(
		MenuElementBase* parentItem, 
		MenuElementBase* prevInListItem,
		const char* name,
		uint16_t parametr, 
		intTune* tune
		);
	
	MenuElement(
		MenuElementBase* parentItem, 
		MenuElementBase* prevInListItem,
		const char* name,
		uint16_t parametr, 
		GetNameEndfnc addNameEndFnc);
	
	MenuElement(
		MenuElementBase* parentItem, 
		MenuElementBase* prevInListItem,
		const char* name,
		IntParamfnc downLongPressFnc,
		uint16_t parametr, 
		intTune* tune
		);
	
	MenuElement(
		MenuElementBase* parentItem, 
		MenuElementBase* prevInListItem,
		const char* name,
		IntParamfnc downLongPressFnc
		);
	
	MenuElement(
			MenuElementBase* parentItem, 
		MenuElementBase* prevInListItem,
		const char* name,
		uint16_t parametr, 
		IntParamfnc downLongPressFnc);	
	
	MenuElement(
			MenuElementBase* parentItem, 
		MenuElementBase* prevInListItem,
		const char* name,
		IntParamfnc onSelectFnc,
		IntParamfnc downLongPressFnc,
		uint16_t parametr, 
		intTune* tune);
	
	MenuElement(
		MenuElementBase* parentItem, 
		MenuElementBase* prevInListItem,
		const char* name,
		IntParamfnc onSelectFnc,
		IntParamfnc downLongPressFnc);	
	
	void invokeDownLongPress();
	void invokeOnSelect();
	
	virtual void saveParametr();
	
	virtual void fillTextScreenElement(Text_ScreenElement* element);

	virtual void init();

	
	intTune* Tune = nullptr;
	uint16_t Parametr;
	GetNameEndfnc AddNameEndFnc = nullptr;
	
protected:	
	IntParamfnc DownLongPressFnc = nullptr;
	IntParamfnc OnSelectFnc = nullptr;
		
private:
	void invokeLongPress();
};

//menu int selector

class MenuElementIntSelector : public MenuElement
{
public:
	
	MenuElementIntSelector(
		MenuElementBase* parentItem, 
		MenuElementBase* prevInListItem,
		const char* name,
		uint16_t initVal, 
		uint16_t minVal, 
		uint16_t maxVal,
		uint16_t step,
		intTune* tune);
	
	MenuElementIntSelector(
		MenuElementBase* parentItem, 
		MenuElementBase* prevInListItem,
		const char* name,
		uint16_t initVal, 
		uint16_t minVal, 
		uint16_t maxVal,
		uint16_t step,
		intTune* tune,
		IntParamfnc downLongPressFnc);
	
	MenuElementIntSelector(
		MenuElementBase* parentItem, 
		MenuElementBase* prevInListItem,
		const char* name,
		uint16_t initVal, 
		uint16_t minVal, 
		uint16_t maxVal,
		uint16_t step,
		intTune* tune,
		IntParamfnc onSelectFnc,
		IntParamfnc downLongPressFnc
		);
	
	virtual void fillTextScreenElement(Text_ScreenElement* element);
	virtual MenuElementBase* GetPrevItem();
	virtual MenuElementBase* GetNextItem();	
	virtual void init();

	
	
protected:
	
	uint16_t InitVal; 
	uint16_t MinVal; 
	uint16_t MaxVal; 
	uint16_t Step; 

	
}
;

//menu objects selector


#endif
