
#ifndef __MENU__H
#define __MENU__H


#pragma once
#include "main.h"
#include "MenuItemClass.h"
#include "MenuClass.h"
#include "string.h"

	bool nullPLUG(uint16_t param);
	bool changeModeIndex(uint16_t param);
	void initMenu();
	

	//menu items constructors

	extern menuItem * plugItem;
	//root
	extern menuItem * modeItem;

	extern menuItem * dateTimeItem;
	extern menuItem * settingsItem;
	
	//extern LCDMenu * mainMenu;

	
	//ROOT MENU

	

#endif 