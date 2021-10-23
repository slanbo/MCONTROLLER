#ifndef __MENUELEMENT__H
#define __MENUELEMENT__H

#include <string>
#include "TuneObjectsExt.hpp"

#define NAME_LENGHT 32

using BaseItemLPfnc = bool(*)();
using IntParamItemLPfnc = bool(*)(uint16_t param);

class MenuElementBase
{
public:
	
	MenuElementBase(std::string name,
		MenuElementBase* parentItem, 
		MenuElementBase* prevInListItem);
	
	MenuElementBase(std::string name,
		MenuElementBase* parentItem, 
		MenuElementBase* prevInListItem,
		BaseItemLPfnc downLongPressFnc);
	
	~MenuElementBase();
		
	virtual void FillScreen();
	
	virtual void invokeDownLongPress();
	
	virtual MenuElementBase* GetPrevItem();
	virtual MenuElementBase* GetNextItem();	
	
	
	char Name[NAME_LENGHT] = { 0 };
	
	BaseItemLPfnc DownLongPressFnc = nullptr;
	MenuElementBase* PrevInListItem = nullptr;
	MenuElementBase* NextInListItem = nullptr;
	MenuElementBase* ParentItem = nullptr;
	MenuElementBase* ChildItem = nullptr;
	MenuElementBase* PrevItem = nullptr;
	MenuElementBase* NextItem = nullptr;
	
protected:
	
	
};

class MenuElement : public MenuElementBase
{
public:
	
	MenuElement(std::string name,
		MenuElementBase* parentItem, 
		MenuElementBase* prevInListItem,
		uint16_t parametr, 
		intTune* tune);
	
	MenuElement(std::string name,
		MenuElementBase* parentItem, 
		MenuElementBase* prevInListItem,
		IntParamItemLPfnc downLongPressFnc,
		uint16_t parametr, 
		intTune* tune);
	
	void invokeDownLongPress();
	
	virtual void saveParametr();
	
	intTune* Tune = nullptr;
	bool selected = false;
	
protected:	
	uint16_t Parametr;
	IntParamItemLPfnc DownLongPressFnc = nullptr;

	
private:
	void invokeLongPress();
};

//menu int selector



//menu objects selector


#endif
