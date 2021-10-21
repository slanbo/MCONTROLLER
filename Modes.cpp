#include "Modes.hpp"
#include "Tunes.hpp"
#include "Lcd_Driver.h"
#include "Controls.hpp"
#include "PCounters.hpp"

char habitatName[40] = "Контр. среды:";
Habitat HabitatMode(
	habitatName,
	0,
	&infoRect,
	5,
	&airTempContr,
	&batTempContr,
	&coContr,
	&lightControl,
	&dayPCounter,
	&nightPCounter,
	&modeIndex);

char beerPreparingName[40] = "Пригот. пива";
BeerPreparing BeerPreparingMode(
	beerPreparingName,
	1,
	&infoRect,
	5,
	&modeIndex,
	&beerModeIndex,
	&boilingControl,
	&mashingControl,
	&pumpControl);

char dryingName[40] = "Сушка";
Drying DryingMode(
	dryingName,
	2,
	&infoRect,
	5,
	&dryingTempContr,
	&dryingHumidityContr,
	&dayPCounter,
	&nightPCounter,
	&modeIndex
	);