#ifndef __MENU_ELEMENTS_OBJECTS__H
#define __MENU_ELEMENTS_OBJECTS__H


#include "MenuElement.hpp"
#include "MenuElements.hpp"
#include "IRMotionSensor.hpp"

MenuElement mi_0(nullptr, nullptr, "Режим работы");
MenuElement mi_1(nullptr, &mi_0, "Дата время");	
MenuElement mi_2(nullptr, &mi_1, "Настройки"); 

//режим работы
MenuElement mi_3(&mi_0, &mi_2, "Контр. среды", 0, &modeIndex);
MenuElement mi_4(&mi_0, &mi_3, "Пригот. пива", 1, &modeIndex);	
MenuElement mi_5(&mi_0, &mi_4, "Контр. сушки", 2, &modeIndex); 
MenuElement mi_6(&mi_0, &mi_5, "Контр. бани", 3, &modeIndex); 
	
//дата и время
MenuElement mi_7(&mi_1, &mi_6, "Дата");
MenuElementIntSelector mi_8(&mi_7, &mi_7, "Знач. даты", 1, 1, 31, 1, &dateTune, restoreDate, setDate);

MenuElement mi_9(&mi_1, &mi_8, "Месяц");
MenuElementIntSelector mi_10(&mi_9, &mi_9, "Знач. месяца", 1, 1, 12, 1, &monthTune, restoreMonth, setMonth);
	
MenuElement mi_11(&mi_1, &mi_10, "Год");
MenuElementIntSelector mi_12(&mi_11, &mi_11, "Знач. года", 2021, 2021, 2031, 1, &yearTune, restoreYear, setYear);
	
MenuElement mi_13(&mi_1, &mi_12, "Час");
MenuElementIntSelector mi_14(&mi_13, &mi_13, "Знач. часа", 0, 0, 24, 1, &hourTune, restoreHour, setHour);

MenuElement mi_15(&mi_1, &mi_14, "Минута");
MenuElementIntSelector mi_16(&mi_15, &mi_15, "Знач. минуты", 1, 1, 60, 1, &minuteTune, restoreMinute, setMinute);
	
MenuElement mi_17(&mi_1, &mi_16, "День недели");
MenuElementIntSelector mi_18(&mi_17, &mi_17, "Знач. дня недели", 1, 1, 7, 1, &weekDayTune, restoreWeekDay, setWeekDay);
	
//настройки
MenuElement mi_19(&mi_2, &mi_18, "Восст. умолч.", setDefaults);
MenuElement mi_20(&mi_2, &mi_19, "Обнул. счетч.", clearCounters);
MenuElement mi_21(&mi_2, &mi_20, "Разъемы");
	
//разъемы
MenuElement mi_22(&mi_21, &mi_21, "Верхняя розетка");
MenuElementIntSelector mi_23(&mi_22, &mi_22, "Подключ. мощн.", 1, 0, 9000, 100, &upSocketLoadPower, setUpSocketLoadPower);

MenuElement mi_24(&mi_21, &mi_23, "Разъем 12 вольт");
MenuElementIntSelector mi_25(&mi_24, &mi_24, "Подключ. мощн.", 1, 0, 1000, 1, &v12LoadPower, setV12SocketLoadPower);

MenuElement mi_26(&mi_21, &mi_25, "Нижняя розетка");
MenuElementIntSelector mi_27(&mi_26, &mi_26, "Подключ. мощн.", 1, 0, 9000, 100, &downSocketLoadPower, setDownSocketLoadPower);
	
//Контроль среды
MenuElement mi_28(&mi_3, &mi_27, "Темп. возд.");
MenuElement mi_29(&mi_3, &mi_28, "Темп. бат.");
MenuElement mi_30(&mi_3, &mi_29, "Угарн. газ");
MenuElement mi_31(&mi_3, &mi_30, "Освещенность");

//"Температ. возд."
MenuElement mi_32(&mi_28, &mi_31, "Фиксир. t", 3, &airTempControlTimeProfile);
MenuElementIntSelector mi_33(&mi_32, &mi_32, "Знач. температуры", 0, 0, 35, 1, &airFixTemp);
	
MenuElement mi_34(&mi_28, &mi_33, "Присутствие", 0, &airTempControlTimeProfile);
MenuElement mi_35(&mi_28, &mi_34, "Отсутствие", 1, &airTempControlTimeProfile);
MenuElement mi_36(&mi_28, &mi_35, "Выходные вт. пт.", 2, &airTempControlTimeProfile);

MenuElement mi_37(&mi_28, &mi_36, "Вкл./Выкл");
MenuElement mi_38(&mi_37, &mi_37, "Включить", 1, &airTempControlOnOffTune);
MenuElement mi_39(&mi_37, &mi_38, "Выключить", 0, &airTempControlOnOffTune);
MenuElement mi_40(&mi_37, &mi_39, "Вкл. по движ.", 2, &airTempControlOnOffTune);
MenuElementIntSelector mi_41(&mi_40, &mi_40, "Анализ за сек.", 1, 0, IR_MOTION_BUFFER_SIZE, 60, &airTempControlSwichOnIfMotionPeriod);
	
//"Температ. бат."
MenuElement mi_42(&mi_29, &mi_41, "День ночь:", 0, &batTempControlTimeProfile);
MenuElement mi_183(&mi_42, &mi_42, "День:");
MenuElementIntSelector mi_180(&mi_183, &mi_183, "Знач. дневн. t", 1, 0, 100, 1, &batDayFixTemp);
MenuElement mi_184(&mi_42, &mi_180, "Ночь:");
MenuElementIntSelector mi_43(&mi_184, &mi_184, "Знач. ночн. t", 1, 0, 100, 1, &batNightFixTemp);

MenuElement mi_44(&mi_29, &mi_43, "Вкл->/Выкл");
MenuElement mi_45(&mi_44, &mi_44, "Включить", 1, &batTempControlOnOffTune);
MenuElement mi_46(&mi_44, &mi_45, "Выключить", 0, &batTempControlOnOffTune);

	
//"Угарный газ"
MenuElement mi_47(&mi_30, &mi_46, "Ноль. уров. CO", 0, &COControlTimeProfile);
MenuElementIntSelector mi_48(&mi_47, &mi_47, "Опасн. ур. CO", 0, 0, 200, 1, &CODangerLevel);
	
MenuElement mi_49(&mi_30, &mi_48, "Вкл./Выкл");
MenuElement mi_50(&mi_49, &mi_49, "Включить", 1, &coControlOnOffTune);
MenuElement mi_51(&mi_49, &mi_50, "Выключить", 0, &coControlOnOffTune);
MenuElement mi_181(&mi_49, &mi_51, "Вкл. по движ.", 2, &coControlOnOffTune);
MenuElementIntSelector mi_182(&mi_49, &mi_181, "Анализ за сек.", 2, 0, IR_MOTION_BUFFER_SIZE, 1, &COControlSwichOnIfMotionPeriod);
	
//"Освещенность"
MenuElement mi_52(&mi_31, &mi_182, "Ночь выключено.", 0, &lightControlTimeProfile);
MenuElementIntSelector mi_53(&mi_52, &mi_52, "Порог выключения", 1, 0, 4065, 5, &LightEdge);

MenuElement mi_54(&mi_31, &mi_53, "Всегда включено", 1, &lightControlTimeProfile);
MenuElementIntSelector mi_55(&mi_54, &mi_54, "Порог выключения", 1, 0, 4065, 5, &LightEdge);

MenuElement mi_56(&mi_31, &mi_55, "Задержка выключения");
MenuElementIntSelector mi_57(&mi_56, &mi_56, "Знач. задерж. сек.", 1, 0, 3600, 60, &LightSwitchOffDelay);

MenuElement mi_58(&mi_31, &mi_57, "Вкл./Выкл");
MenuElement mi_59(&mi_58, &mi_58, "Включить", 1, &lightControlOnOffTune);
MenuElement mi_60(&mi_58, &mi_59, "Выключить", 0, &lightControlOnOffTune);
MenuElement mi_61(&mi_37, &mi_60, "Вкл. по движ.", 2, &lightControlOnOffTune);
MenuElementIntSelector mi_62(&mi_61, &mi_61, "Анализ за сек.", 2, 0, IR_MOTION_BUFFER_SIZE, 1, &lightControlSwichOnIfMotionPeriod);

//приготовление пива
//mashing
MenuElement mi_63(&mi_4, &mi_62, "Темп. паузы", 0, &beerModeIndex);

MenuElement mi_Pause__45_52_68_72_79(&mi_63, &mi_63, "45|48|57|62|70|79", 1, restorePauses);
MenuElement mi_Pause__62_68_72_81(&mi_63, &mi_Pause__45_52_68_72_79, "48|57|68|79", 2, restorePauses);
MenuElement mi_Pause__30_100c(&mi_63, &mi_Pause__62_68_72_81, "20_20c", 3, restorePauses);

MenuElement mi_StartFromBegin(&mi_63, &mi_Pause__30_100c, "Старт с начала", 1, startPauses);
MenuElement mi_StartFromSaved(&mi_63, &mi_StartFromBegin, "Продолжить", 2, startPauses);
MenuElement mi_StartFromTemperature(&mi_63, &mi_StartFromSaved, "Старт с темп.", 3, startPauses);

//mashing Pause 1
MenuElement mi_64(&mi_63, &mi_StartFromTemperature, "П1:", 1, AddMashingPauseDescription);
MenuElement mi_65(&mi_64, &mi_64, "П1 темп.", 1, AddChildTuneValue);
MenuElementIntSelector mi_66(&mi_65, &mi_65, "П1 температ.", 1, 0, 100, 5, &mashingPause1Temp);
MenuElement mi_67(&mi_64, &mi_66, "П1 время", 1, AddChildTuneValue);
MenuElementIntSelector mi_68(&mi_67, &mi_67, "П1 время", 1, 0, 7200, 300, &mashingPause1Time);
MenuElement p1_onoff(&mi_64, &mi_68, "Вкл/Выкл");
MenuElement p1_on(&p1_onoff, &p1_onoff, "Вкл", 1, &mashingPause1Active);
MenuElement p1_off(&p1_onoff, &p1_on, "Выкл", 0, &mashingPause1Active);


//mashing Pause 2
MenuElement mi_69(&mi_63, &p1_off, "П2:", 2, AddMashingPauseDescription);
MenuElement mi_70(&mi_69, &mi_69, "П2 темп.", 2, AddChildTuneValue);
MenuElementIntSelector mi_71(&mi_70, &mi_70, "П2 температ.", 1, 0, 100, 5, &mashingPause2Temp);
MenuElement mi_72(&mi_69, &mi_71, "П2 время", 2, AddChildTuneValue);
MenuElementIntSelector mi_73(&mi_72, &mi_72, "П2 время", 1, 0, 7200, 300, &mashingPause2Time);
MenuElement p2_onoff(&mi_69, &mi_73, "Вкл/Выкл");
MenuElement p2_on(&p2_onoff, &p2_onoff, "Вкл", 1, &mashingPause2Active);
MenuElement p2_off(&p2_onoff, &p2_on, "Выкл", 0, &mashingPause2Active);


//mashing Pause 3
MenuElement mi_74(&mi_63, &p2_off, "П3:", 3, AddMashingPauseDescription);
MenuElement mi_75(&mi_74, &mi_74, "П3 темп.", 3, AddChildTuneValue);
MenuElementIntSelector mi_76(&mi_75, &mi_75, "П3 температ.", 1, 0, 100, 5, &mashingPause3Temp);
MenuElement mi_77(&mi_74, &mi_76, "П3 время", 3, AddChildTuneValue);
MenuElementIntSelector mi_78(&mi_77, &mi_77, "П3 время", 1, 0, 7200, 300, &mashingPause3Time);
MenuElement p3_onoff(&mi_74, &mi_78, "Вкл/Выкл");
MenuElement p3_on(&p3_onoff, &p3_onoff, "Вкл", 1, &mashingPause3Active);
MenuElement p3_off(&p3_onoff, &p3_on, "Выкл", 0, &mashingPause3Active);


//mashing Pause 4
MenuElement mi_79(&mi_63, &p3_off, "П4:", 4, AddMashingPauseDescription);
MenuElement mi_80(&mi_79, &mi_79, "П4 темп.", 4, AddChildTuneValue);
MenuElementIntSelector mi_81(&mi_80, &mi_80, "П4 температ.", 1, 0, 100, 5, &mashingPause4Temp);
MenuElement mi_82(&mi_79, &mi_81, "П4 время", 4, AddChildTuneValue);
MenuElementIntSelector mi_83(&mi_82, &mi_82, "П4 время", 1, 0, 7200, 100, &mashingPause4Time);
MenuElement p4_onoff(&mi_79, &mi_83, "Вкл/Выкл");
MenuElement p4_on(&p4_onoff, &p4_onoff, "Вкл", 1, &mashingPause4Active);
MenuElement p4_off(&p4_onoff, &p4_on, "Выкл", 0, &mashingPause4Active);


//mashing Pause 5
MenuElement mi_84(&mi_63, &p4_off, "П5:", 5, AddMashingPauseDescription);
MenuElement mi_85(&mi_84, &mi_84, "П5 темп.", 5, AddChildTuneValue);
MenuElementIntSelector mi_86(&mi_85, &mi_85, "П5 температ.", 1, 0, 100, 5, &mashingPause5Temp);
MenuElement mi_87(&mi_84, &mi_86, "П5 время", 5, AddChildTuneValue);
MenuElementIntSelector mi_88(&mi_87, &mi_87, "П5 время", 1, 0, 7200, 100, &mashingPause5Time);
MenuElement p5_onoff(&mi_84, &mi_88, "Вкл/Выкл");
MenuElement p5_on(&p5_onoff, &p5_onoff, "Вкл", 1, &mashingPause5Active);
MenuElement p5_off(&p5_onoff, &p5_on, "Выкл", 0, &mashingPause5Active);


//mashing Pause 6
MenuElement mi_89(&mi_63, &p5_off, "П6:", 6, AddMashingPauseDescription);
MenuElement mi_90(&mi_89, &mi_89, "П6 темп.", 6, AddChildTuneValue);
MenuElementIntSelector mi_91(&mi_90, &mi_90, "П6 температ.", 1, 0, 100, 5, &mashingPause6Temp);
MenuElement mi_92(&mi_89, &mi_91, "П6 время", 6, AddChildTuneValue);
MenuElementIntSelector mi_93(&mi_92, &mi_92, "П6 время", 1, 0, 7200, 100, &mashingPause6Time);
MenuElement p6_onoff(&mi_89, &mi_93, "Вкл/Выкл");
MenuElement p6_on(&p6_onoff, &p6_onoff, "Вкл", 1, &mashingPause6Active);
MenuElement p6_off(&p6_onoff, &p6_on, "Выкл", 0, &mashingPause6Active);
	
MenuElement mi_94(&mi_4, &p6_off, "Варка", 1, &beerModeIndex);
MenuElement mi_BoilingPause_98_15_98_60_98_60(&mi_94, &mi_94, "10|60|10", 4, restorePauses);
MenuElement mi_BoilingStartFromBegin(&mi_94, &mi_BoilingPause_98_15_98_60_98_60, "Старт с начала", 1, startPauses);
MenuElement mi_BoilingStartFromSaved(&mi_94, &mi_BoilingStartFromBegin, "Продолжить", 2, startPauses);

//boiling Pause 1
MenuElement mi_95(&mi_94, &mi_BoilingStartFromSaved, "П1:", 1, AddBoilingPauseDescription);
MenuElement mi_96(&mi_95, &mi_95, "П1 темп.", 1, AddChildTuneValue);
MenuElementIntSelector mi_97(&mi_96, &mi_96, "П1 температ.", 1, 0, 100, 5, &boilingPause1Temp);
MenuElement mi_98(&mi_95, &mi_97, "П1 время", 1, AddChildTuneValue);
MenuElementIntSelector mi_99(&mi_98, &mi_98, "П1 время", 1, 0, 7200, 100, &boilingPause1Time);
MenuElement bp1_onoff(&mi_95, &mi_99, "Вкл/Выкл");
MenuElement bp1_on(&bp1_onoff, &bp1_onoff, "Вкл", 1, &boilingPause1Active);
MenuElement bp1_off(&bp1_onoff, &bp1_on, "Выкл", 0, &boilingPause1Active);

//boiling Pause 2
MenuElement mi_100(&mi_94, &bp1_off, "П2:", 2, AddBoilingPauseDescription);
MenuElement mi_101(&mi_100, &mi_100, "П2 темп.", 2, AddChildTuneValue);
MenuElementIntSelector mi_102(&mi_101, &mi_101, "П2 температ.", 1, 0, 100, 5, &boilingPause2Temp);
MenuElement mi_103(&mi_100, &mi_102, "П2 время", 2, AddChildTuneValue);
MenuElementIntSelector mi_104(&mi_103, &mi_103, "П2 время", 1, 0, 7200, 100, &boilingPause2Time);
MenuElement bp2_onoff(&mi_100, &mi_104, "Вкл/Выкл");
MenuElement bp2_on(&bp2_onoff, &bp2_onoff, "Вкл", 1, &boilingPause2Active);
MenuElement bp2_off(&bp2_onoff, &bp2_on, "Выкл", 0, &boilingPause2Active);

//boiling Pause 3
MenuElement mi_105(&mi_94, &bp2_off, "П3:", 3, AddBoilingPauseDescription);
MenuElement mi_106(&mi_105, &mi_105, "П3 темп.", 3, AddChildTuneValue);
MenuElementIntSelector mi_107(&mi_106, &mi_106, "П3 температ.", 1, 0, 100, 5, &boilingPause3Temp);
MenuElement mi_108(&mi_105, &mi_107, "П3 время", 3, AddChildTuneValue);
MenuElementIntSelector mi_109(&mi_108, &mi_108, "П3 время", 1, 0, 7200, 100, &boilingPause3Time);
MenuElement bp3_onoff(&mi_105, &mi_109, "Вкл/Выкл");
MenuElement bp3_on(&bp3_onoff, &bp3_onoff, "Вкл", 1, &boilingPause3Active);
MenuElement bp3_off(&bp3_onoff, &bp3_on, "Выкл", 0, &boilingPause3Active);
	
//pump
MenuElement mi_pump(&mi_4, &bp3_off, "Насос");
MenuElement mi_pumppausesmode(&mi_pump, &mi_pump, "Паузами", ChangePumpMode, 1, &PumpMode);
MenuElement mi_pumpon(&mi_pumppausesmode, &mi_pumppausesmode, "Пауза вкл.");
MenuElementIntSelector mi_pumponperiod(&mi_pumpon, &mi_pumpon, "Пер. вкл. (сек.)", 60, 0, 1200, 60, &SwitchedOnPumpTime);
MenuElement mi_pumpoff(&mi_pumppausesmode, &mi_pumponperiod, "Пауза выкл.");
MenuElementIntSelector mi_pumpoffperiod(&mi_pumpoff, &mi_pumpoff, "Пер. выкл. (сек.)", 60, 0, 1200, 60, &SwitchedOffPumpTime);
MenuElement mi_pumpheatingmode(&mi_pump, &mi_pumpoffperiod, "При нагреве", ChangePumpMode, 2, &PumpMode);
MenuElement mi_pumpstayonmode(&mi_pump, &mi_pumpheatingmode, "При паузе", ChangePumpMode, 3, &PumpMode);
MenuElement mi_pumpalltimeonmode(&mi_pump, &mi_pumpstayonmode, "Всегда вкл.", ChangePumpMode, 4, &PumpMode);
MenuElement mi_pumpoffmode(&mi_pump, &mi_pumpalltimeonmode, "Выкл.", ChangePumpMode, 5, &PumpMode);

//отложенный старт
MenuElement mi_110(nullptr, &mi_pumpoffmode, "Отлож. старт");
	
//дата начала 
MenuElement mi_111(&mi_110, &mi_110, "Дата старт", restoreDelayBeginTunes);
	
MenuElement mi_112(&mi_111, &mi_111, "Год");
MenuElementIntSelector mi_113(&mi_112, &mi_112, "Знач. года", 21, 21, 31, 1, &delayBeginYear);
	
MenuElement mi_114(&mi_111, &mi_113, "Месяц");
MenuElementIntSelector mi_115(&mi_114, &mi_114, "Знач. месяца", 1, 1, 12, 1, &delayBeginMonth);
	
MenuElement mi_116(&mi_111, &mi_115, "День");
MenuElementIntSelector mi_117(&mi_116, &mi_116, "Знач. дня", 1, 1, 31, 1, &delayBeginDate);
	
MenuElement mi_118(&mi_111, &mi_117, "Час");
MenuElementIntSelector mi_119(&mi_118, &mi_118, "Знач. часа", 0, 0, 24, 1, &delayBeginHour);
	
MenuElement mi_120(&mi_111, &mi_119, "Минута");
MenuElementIntSelector mi_121(&mi_120, &mi_120, "Знач. минуты", 1, 0, 60, 1, &delayBeginMinute);
	
	
//вкл выкл
MenuElement mi_122(&mi_110, &mi_121, "Вкл/Выкл");
	
MenuElement mi_123(&mi_122, &mi_122, "Включить", 1, &delayBeginOnOffTune);
MenuElement mi_124(&mi_122, &mi_123, "Выключить", 0, &delayBeginOnOffTune);
	
//отложенный стоп
MenuElement mi_125(nullptr, &mi_124, "Отлож. стоп");
	
//дата стоп 
MenuElement mi_126(&mi_125, &mi_125, "Дата стоп", restoreDelayEndTunes);
	
MenuElement mi_127(&mi_126, &mi_126, "Год");
MenuElementIntSelector mi_128(&mi_127, &mi_127, "Знач. года", 21, 21, 31, 1, &delayEndYear);
	
MenuElement mi_129(&mi_126, &mi_128,"Месяц");
MenuElementIntSelector mi_130(&mi_129, &mi_129, "Знач. месяца", 1, 1, 12, 1, &delayEndMonth);
	
MenuElement mi_131(&mi_126, &mi_130, "День");
MenuElementIntSelector mi_132(&mi_131, &mi_131, "Знач. дня", 1, 1, 31, 1, &delayEndDate);
	
MenuElement mi_133(&mi_126, &mi_132, "Час");
MenuElementIntSelector mi_134(&mi_133, &mi_133, "Знач. часа", 1, 0, 24, 1, &delayEndHour);
	
MenuElement mi_135(&mi_126, &mi_134, "Минута");
MenuElementIntSelector mi_136(&mi_135, &mi_135, "Знач. минуты", 1, 0, 60, 1, &delayEndMinute);
	
//вкл выкл

MenuElement mi_137(&mi_125, &mi_136, "Вкл/Выкл");
	
MenuElement mi_138(&mi_137, &mi_137, "Включить", 1, &delayEndOnOffTune);
MenuElement mi_139(&mi_137, &mi_138, "Выключить", 0, &delayEndOnOffTune);
	
/*	
//контроль сушки
MenuElement mi_140(&mi_5, &mi_139, "Температ. возд.");
MenuElement mi_141(&mi_140, &mi_140, "Фиксированная t", 0, &dryingAirTempProfileIndex);
MenuElementIntSelector mi_142(&mi_141, &mi_141, "Температура = ", 50, 20, 80, 5, &dryingFixTemp);
	
MenuElement mi_143(&mi_140, &mi_142, "День ночь", 1, &dryingAirTempProfileIndex);
MenuElement mi_144(&mi_143, &mi_143, "Темпер. день");
MenuElementIntSelector mi_145(&mi_144, &mi_144, "Температура = ", 20, 20, 80, 5, &dryingFixTempDay);	
	
MenuElement mi_146(&mi_143, &mi_145, "Темпер. ночь");
MenuElementIntSelector mi_147(&mi_146, &mi_146, "Температура = ", 20, 20, 80, 5, &dryingFixTempNight);
	
MenuElement mi_148(&mi_140, &mi_147, "Вкл./Выкл.");
MenuElement mi_149(&mi_148, &mi_148, "Включен", 1, &dryingTempOnOffTune);
MenuElement mi_150(&mi_148, &mi_149, "Выключен", 0, &dryingTempOnOffTune);

MenuElement mi_151(&mi_5, &mi_150, "Влажность. возд.");
MenuElement mi_152(&mi_151, &mi_151, "Влажность меньш. ");
MenuElementIntSelector mi_153(&mi_152, &mi_152, "Влажность < ", 1, 1, 4065, 100, &DryingDryLevel);
	
MenuElement mi_154(&mi_151, &mi_153, "Вкл./Выкл.");
MenuElement mi_155(&mi_154, &mi_154, "Включен", 1, &dryingHumidityOnOffTune);
MenuElement mi_156(&mi_154, &mi_155, "Выключен", 0, &dryingHumidityOnOffTune);
	
MenuElement mi_157(&mi_5, &mi_156, "Вентилятор");
	
MenuElement mi_158(&mi_157, &mi_157, "Всегда вкл.", 0, &dryingVentMode);
MenuElement mi_159(&mi_157, &mi_158, "Вкл при нагр.", 1, &dryingVentMode);
	
MenuElement mi_160(&mi_157, &mi_159, "Вкл паузами.", 2, &dryingVentMode);
MenuElement mi_161(&mi_160, &mi_160, "Период вкл.");
MenuElementIntSelector mi_162(&mi_161, &mi_161, "Сек. включено", 600, 1, 4065, 10, &dryingVentOnPeriod);
MenuElement mi_163(&mi_160, &mi_162, "Период выкл");
MenuElementIntSelector mi_164(&mi_163, &mi_163, "Сек. выключено", 600, 1, 4065, 10, &dryingVentOffPeriod);
	
MenuElement mi_165(&mi_157, &mi_164, "Вкл./Выкл.");
MenuElement mi_166(&mi_165, &mi_165, "Включен", 1, &dryingVentOnOffTune);
MenuElement mi_167(&mi_165, &mi_166, "Выключен", 0, &dryingVentOnOffTune);

MenuElement mi_168(&mi_31, &mi_167, "Активир. по движ."); //habitat light ->

MenuElement mi_169(&mi_168, &mi_168, "Вкл./Выкл.");
MenuElement mi_170(&mi_169, &mi_169, "Включен", 1, &MotionControlOnOffTune);
MenuElement mi_171(&mi_169, &mi_170, "Выключен", 0, &MotionControlOnOffTune);

MenuElement mi_172(&mi_168, &mi_171, "Анализ. движ за.");
MenuElementIntSelector mi_173(&mi_172, &mi_172, "Время сек.", 2, 0, IR_MOTION_BUFFER_SIZE, 1, &OnIfMotionPeriod);

MenuElement mi_174(&mi_28, &mi_173, "Активир. по движ.");   //habitat air temp ->

MenuElement mi_175(&mi_174, &mi_174, "Вкл./Выкл.");
MenuElement mi_176(&mi_175, &mi_175, "Включен", 1, &longPeriodMotionControlOnOffTune);
MenuElement mi_177(&mi_175, &mi_176, "Выключен", 0, &longPeriodMotionControlOnOffTune);

MenuElement mi_178(&mi_174, &mi_177, "Анализ. движ за.");
MenuElementIntSelector mi_179(&mi_178, &mi_178, "Время сек.", 2, 0, IR_MOTION_BUFFER_SIZE, 1, &longPeriodOnIfMotionPeriod);*/

#endif