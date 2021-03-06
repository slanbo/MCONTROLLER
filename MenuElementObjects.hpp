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
MenuElement mi_Pause__30_100c(&mi_63, &mi_Pause__62_68_72_81, "25_180c", 3, restorePauses);

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
MenuElement p1_start(&mi_64, &p1_off, "Старт с паузы", 1, MashingPauseStart);

//mashing Pause 2
MenuElement mi_69(&mi_63, &p1_start, "П2:", 2, AddMashingPauseDescription);
MenuElement mi_70(&mi_69, &mi_69, "П2 темп.", 2, AddChildTuneValue);
MenuElementIntSelector mi_71(&mi_70, &mi_70, "П2 температ.", 1, 0, 100, 5, &mashingPause2Temp);
MenuElement mi_72(&mi_69, &mi_71, "П2 время", 2, AddChildTuneValue);
MenuElementIntSelector mi_73(&mi_72, &mi_72, "П2 время", 1, 0, 7200, 300, &mashingPause2Time);
MenuElement p2_onoff(&mi_69, &mi_73, "Вкл/Выкл");
MenuElement p2_on(&p2_onoff, &p2_onoff, "Вкл", 1, &mashingPause2Active);
MenuElement p2_off(&p2_onoff, &p2_on, "Выкл", 0, &mashingPause2Active);
MenuElement p2_start(&mi_69, &p2_off, "Старт с паузы", 2, MashingPauseStart);


//mashing Pause 3
MenuElement mi_74(&mi_63, &p2_start, "П3:", 3, AddMashingPauseDescription);
MenuElement mi_75(&mi_74, &mi_74, "П3 темп.", 3, AddChildTuneValue);
MenuElementIntSelector mi_76(&mi_75, &mi_75, "П3 температ.", 1, 0, 100, 5, &mashingPause3Temp);
MenuElement mi_77(&mi_74, &mi_76, "П3 время", 3, AddChildTuneValue);
MenuElementIntSelector mi_78(&mi_77, &mi_77, "П3 время", 1, 0, 7200, 300, &mashingPause3Time);
MenuElement p3_onoff(&mi_74, &mi_78, "Вкл/Выкл");
MenuElement p3_on(&p3_onoff, &p3_onoff, "Вкл", 1, &mashingPause3Active);
MenuElement p3_off(&p3_onoff, &p3_on, "Выкл", 0, &mashingPause3Active);
MenuElement p3_start(&mi_74, &p3_off, "Старт с паузы", 3, MashingPauseStart);

//mashing Pause 4
MenuElement mi_79(&mi_63, &p3_start, "П4:", 4, AddMashingPauseDescription);
MenuElement mi_80(&mi_79, &mi_79, "П4 темп.", 4, AddChildTuneValue);
MenuElementIntSelector mi_81(&mi_80, &mi_80, "П4 температ.", 1, 0, 100, 5, &mashingPause4Temp);
MenuElement mi_82(&mi_79, &mi_81, "П4 время", 4, AddChildTuneValue);
MenuElementIntSelector mi_83(&mi_82, &mi_82, "П4 время", 1, 0, 7200, 100, &mashingPause4Time);
MenuElement p4_onoff(&mi_79, &mi_83, "Вкл/Выкл");
MenuElement p4_on(&p4_onoff, &p4_onoff, "Вкл", 1, &mashingPause4Active);
MenuElement p4_off(&p4_onoff, &p4_on, "Выкл", 0, &mashingPause4Active);
MenuElement p4_start(&mi_79, &p4_off, "Старт с паузы", 4, MashingPauseStart);

//mashing Pause 5
MenuElement mi_84(&mi_63, &p4_start, "П5:", 5, AddMashingPauseDescription);
MenuElement mi_85(&mi_84, &mi_84, "П5 темп.", 5, AddChildTuneValue);
MenuElementIntSelector mi_86(&mi_85, &mi_85, "П5 температ.", 1, 0, 100, 5, &mashingPause5Temp);
MenuElement mi_87(&mi_84, &mi_86, "П5 время", 5, AddChildTuneValue);
MenuElementIntSelector mi_88(&mi_87, &mi_87, "П5 время", 1, 0, 7200, 100, &mashingPause5Time);
MenuElement p5_onoff(&mi_84, &mi_88, "Вкл/Выкл");
MenuElement p5_on(&p5_onoff, &p5_onoff, "Вкл", 1, &mashingPause5Active);
MenuElement p5_off(&p5_onoff, &p5_on, "Выкл", 0, &mashingPause5Active);
MenuElement p5_start(&mi_84, &p5_off, "Старт с паузы", 5, MashingPauseStart);

//mashing Pause 6
MenuElement mi_89(&mi_63, &p5_start, "П6:", 6, AddMashingPauseDescription);
MenuElement mi_90(&mi_89, &mi_89, "П6 темп.", 6, AddChildTuneValue);
MenuElementIntSelector mi_91(&mi_90, &mi_90, "П6 температ.", 1, 0, 100, 5, &mashingPause6Temp);
MenuElement mi_92(&mi_89, &mi_91, "П6 время", 6, AddChildTuneValue);
MenuElementIntSelector mi_93(&mi_92, &mi_92, "П6 время", 1, 0, 7200, 100, &mashingPause6Time);
MenuElement p6_onoff(&mi_89, &mi_93, "Вкл/Выкл");
MenuElement p6_on(&p6_onoff, &p6_onoff, "Вкл", 1, &mashingPause6Active);
MenuElement p6_off(&p6_onoff, &p6_on, "Выкл", 0, &mashingPause6Active);
MenuElement p6_start(&mi_89, &p6_off, "Старт с паузы", 5, MashingPauseStart);


	
MenuElement mi_94(&mi_4, &p6_start, "Варка", 1, &beerModeIndex);
MenuElement mi_BoilingPause_98_10_60_10(&mi_94, &mi_94, "10|60|10", 4, restorePauses);
MenuElement mi_BoilingStartFromBegin(&mi_94, &mi_BoilingPause_98_10_60_10, "Старт с начала", 1, startPauses);
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
MenuElement bp1_start(&mi_95, &bp1_off, "Старт с паузы", 1, BoilingPauseStart);



//boiling Pause 2
MenuElement mi_100(&mi_94, &bp1_start, "П2:", 2, AddBoilingPauseDescription);
MenuElement mi_101(&mi_100, &mi_100, "П2 темп.", 2, AddChildTuneValue);
MenuElementIntSelector mi_102(&mi_101, &mi_101, "П2 температ.", 1, 0, 100, 5, &boilingPause2Temp);
MenuElement mi_103(&mi_100, &mi_102, "П2 время", 2, AddChildTuneValue);
MenuElementIntSelector mi_104(&mi_103, &mi_103, "П2 время", 1, 0, 7200, 100, &boilingPause2Time);
MenuElement bp2_onoff(&mi_100, &mi_104, "Вкл/Выкл");
MenuElement bp2_on(&bp2_onoff, &bp2_onoff, "Вкл", 1, &boilingPause2Active);
MenuElement bp2_off(&bp2_onoff, &bp2_on, "Выкл", 0, &boilingPause2Active);
MenuElement bp2_start(&mi_100, &bp2_off, "Старт с паузы", 2, BoilingPauseStart);


//boiling Pause 3
MenuElement mi_105(&mi_94, &bp2_start, "П3:", 3, AddBoilingPauseDescription);
MenuElement mi_106(&mi_105, &mi_105, "П3 темп.", 3, AddChildTuneValue);
MenuElementIntSelector mi_107(&mi_106, &mi_106, "П3 температ.", 1, 0, 100, 5, &boilingPause3Temp);
MenuElement mi_108(&mi_105, &mi_107, "П3 время", 3, AddChildTuneValue);
MenuElementIntSelector mi_109(&mi_108, &mi_108, "П3 время", 1, 0, 7200, 100, &boilingPause3Time);
MenuElement bp3_onoff(&mi_105, &mi_109, "Вкл/Выкл");
MenuElement bp3_on(&bp3_onoff, &bp3_onoff, "Вкл", 1, &boilingPause3Active);
MenuElement bp3_off(&bp3_onoff, &bp3_on, "Выкл", 0, &boilingPause3Active);
MenuElement bp3_start(&mi_105, &bp3_off, "Старт с паузы", 2, BoilingPauseStart);

//pump
MenuElement mi_pump(&mi_4, &bp3_start, "Насос");
MenuElement mi_pumppausesmode(&mi_pump, &mi_pump, "Паузами", ChangePumpMode, 1, &PumpMode);
MenuElement mi_pumpon(&mi_pumppausesmode, &mi_pumppausesmode, "Пауза вкл.");
MenuElementIntSelector mi_pumponperiod(&mi_pumpon, &mi_pumpon, "Пер. вкл. (сек.)", 5, 0, 1200, 5, &SwitchedOnPumpTime);
MenuElement mi_pumpoff(&mi_pumppausesmode, &mi_pumponperiod, "Пауза выкл.");
MenuElementIntSelector mi_pumpoffperiod(&mi_pumpoff, &mi_pumpoff, "Пер. выкл. (сек.)", 5, 0, 1200, 5, &SwitchedOffPumpTime);
MenuElement mi_pumpheatingmode(&mi_pump, &mi_pumpoffperiod, "При нагреве", ChangePumpMode, 2, &PumpMode);
MenuElement mi_pumpstayonmode(&mi_pump, &mi_pumpheatingmode, "При паузе", ChangePumpMode, 3, &PumpMode);
MenuElement mi_pumpalltimeonmode(&mi_pump, &mi_pumpstayonmode, "Всегда вкл.", ChangePumpMode, 4, &PumpMode);
MenuElement mi_pumpoffmode(&mi_pump, &mi_pumpalltimeonmode, "Выкл.", ChangePumpMode, 5, &PumpMode);

MenuElement mi_stay_on_delta(&mi_4, &mi_pumpoffmode, "Дельта");
MenuElementIntSelector mi_stay_on_delta_vals(&mi_stay_on_delta, &mi_stay_on_delta, "Дельта. (сек.)", 1, 0, 10, 1, &mashboilStayOnDelta);

//отложенный старт
MenuElement mi_110(nullptr, &mi_stay_on_delta_vals, "Отлож. старт", restoreDelayBeginTunes);
	
//дата начала 
//MenuElement mi_111(&mi_110, &mi_110, "Дата старт", restoreDelayBeginTunes);
	
MenuElement mi_112(&mi_110, &mi_110, "Год", 1, AddChildTuneValue);
MenuElementIntSelector mi_113(&mi_112, &mi_112, "Знач. года", 21, 21, 31, 1, &delayBeginYear, nullptr, DelayBeginOnOff);
	
MenuElement mi_114(&mi_110, &mi_113, "Месяц", 1, AddChildTuneValue);
MenuElementIntSelector mi_115(&mi_114, &mi_114, "Знач. месяца", 1, 1, 12, 1, &delayBeginMonth, nullptr, DelayBeginOnOff);
	
MenuElement mi_116(&mi_110, &mi_115, "День", 1, AddChildTuneValue);
MenuElementIntSelector mi_117(&mi_116, &mi_116, "Знач. дня", 1, 1, 31, 1, &delayBeginDate, nullptr, DelayBeginOnOff);
	
MenuElement mi_118(&mi_110, &mi_117, "Час", 1, AddChildTuneValue);
MenuElementIntSelector mi_119(&mi_118, &mi_118, "Знач. часа", 0, 0, 24, 1, &delayBeginHour, nullptr, DelayBeginOnOff);
	
MenuElement mi_120(&mi_110, &mi_119, "Минута", 1, AddChildTuneValue);
MenuElementIntSelector mi_121(&mi_120, &mi_120, "Знач. минуты", 1, 0, 60, 1, &delayBeginMinute, nullptr, DelayBeginOnOff);
	
	
//вкл выкл
MenuElement mi_122(&mi_110, &mi_121, "Вкл/Выкл");
	
MenuElement mi_123(&mi_122, &mi_122, "Включить", 1, &delayBeginOnOffTune);
MenuElement mi_124(&mi_122, &mi_123, "Выключить", 0, &delayBeginOnOffTune);
	
//отложенный стоп
MenuElement mi_125(nullptr, &mi_124, "Отлож. стоп", restoreDelayEndTunes);
	
//дата стоп 
//MenuElement mi_126(&mi_125, &mi_125, "Дата стоп", restoreDelayEndTunes);
	
MenuElement mi_127(&mi_125, &mi_125, "Год", 1, AddChildTuneValue);
MenuElementIntSelector mi_128(&mi_127, &mi_127, "Знач. года", 21, 21, 31, 1, &delayEndYear, nullptr ,DelayEndOnOff);
	
MenuElement mi_129(&mi_125, &mi_128, "Месяц", 1, AddChildTuneValue);
MenuElementIntSelector mi_130(&mi_129, &mi_129, "Знач. месяца", 1, 1, 12, 1, &delayEndMonth, nullptr, DelayEndOnOff);
	
MenuElement mi_131(&mi_125, &mi_130, "День", 1, AddChildTuneValue);
MenuElementIntSelector mi_132(&mi_131, &mi_131, "Знач. дня", 1, 1, 31, 1, &delayEndDate, nullptr, DelayEndOnOff);
	
MenuElement mi_133(&mi_125, &mi_132, "Час", 1, AddChildTuneValue);
MenuElementIntSelector mi_134(&mi_133, &mi_133, "Знач. часа", 1, 0, 24, 1, &delayEndHour, nullptr, DelayEndOnOff);
	
MenuElement mi_135(&mi_125, &mi_134, "Минута", 1, AddChildTuneValue);
MenuElementIntSelector mi_136(&mi_135, &mi_135, "Знач. минуты", 1, 0, 60, 1, &delayEndMinute, nullptr, DelayEndOnOff);
	
//вкл выкл

MenuElement mi_137(&mi_125, &mi_136, "Вкл/Выкл");
	
MenuElement mi_138(&mi_137, &mi_137, "Включить", 1, &delayEndOnOffTune);
MenuElement mi_139(&mi_137, &mi_138, "Выключить", 0, &delayEndOnOffTune);
	
//drying

MenuElement mi_DryingPause_40_50_60(&mi_5, &mi_139, "40|50|60", 1, restoreDryingPauses);
MenuElement mi_DryingStartFromBegin(&mi_5, &mi_DryingPause_40_50_60, "Старт с начала", 1, startDryingPauses);
MenuElement mi_DryingStartFromSaved(&mi_5, &mi_DryingStartFromBegin, "Продолжить", 2, startDryingPauses);


MenuElement mi_140(&mi_5, &mi_DryingStartFromSaved, "П1:", 1, AddDryingPauseDescription);
MenuElement mi_141(&mi_140, &mi_140, "П1 темп.", 1, AddChildTuneValue);
MenuElementIntSelector mi_142(&mi_141, &mi_141, "П1 температ.", 1, 0, 100, 5, &dryingPause1Temp);
MenuElement mi_143(&mi_140, &mi_142, "П1 время", 1, AddChildTuneValue);
MenuElementIntSelector mi_P1_time(&mi_143, &mi_143, "П1 время", 1, 0, 7200, 100, &dryingPause1Time);
MenuElement dp1_onoff(&mi_140, &mi_P1_time, "Вкл/Выкл");
MenuElement dp1_on(&dp1_onoff, &dp1_onoff, "Вкл", 1, &dryingPause1Active);
MenuElement dp1_off(&dp1_onoff, &dp1_on, "Выкл", 0, &dryingPause1Active);
MenuElement dp1_start(&mi_140, &dp1_off, "Старт с паузы", 1, DryingPauseStart);



//boiling Pause 2
MenuElement mi_144(&mi_5, &dp1_start, "П2:", 2, AddDryingPauseDescription);
MenuElement mi_145(&mi_100, &mi_144, "П2 темп.", 2, AddChildTuneValue);
MenuElementIntSelector mi_146(&mi_101, &mi_145, "П2 температ.", 1, 0, 100, 5, &dryingPause2Temp);
MenuElement mi_147(&mi_100, &mi_146, "П2 время", 2, AddChildTuneValue);
MenuElementIntSelector mi_148(&mi_103, &mi_147, "П2 время", 1, 0, 7200, 100, &dryingPause2Time);
MenuElement dp2_onoff(&mi_100, &mi_148, "Вкл/Выкл");
MenuElement dp2_on(&bp2_onoff, &dp2_onoff, "Вкл", 1, &dryingPause2Active);
MenuElement dp2_off(&bp2_onoff, &dp2_on, "Выкл", 0, &dryingPause2Active);
MenuElement dp2_start(&mi_100, &dp2_off, "Старт с паузы", 2, DryingPauseStart);


//boiling Pause 3
MenuElement mi_149(&mi_5, &dp2_start, "П3:", 3, AddDryingPauseDescription);
MenuElement mi_150(&mi_105, &mi_149, "П3 темп.", 3, AddChildTuneValue);
MenuElementIntSelector mi_152(&mi_106, &mi_150, "П3 температ.", 1, 0, 100, 5, &dryingPause3Temp);
MenuElement mi_153(&mi_105, &mi_152, "П3 время", 3, AddChildTuneValue);
MenuElementIntSelector mi_154(&mi_108, &mi_153, "П3 время", 1, 0, 7200, 100, &dryingPause3Time);
MenuElement dp3_onoff(&mi_105, &mi_154, "Вкл/Выкл");
MenuElement dp3_on(&bp3_onoff, &dp3_onoff, "Вкл", 1, &dryingPause3Active);
MenuElement dp3_off(&bp3_onoff, &dp3_on, "Выкл", 0, &dryingPause3Active);
MenuElement dp3_start(&mi_105, &dp3_off, "Старт с паузы", 2, DryingPauseStart);

//vent
MenuElement mi_vent(&mi_5, &dp3_start, "Вентилятор");
MenuElement mi_ventpausesmode(&mi_vent, &mi_vent, "Паузами", ChangeVentMode, 1, &dryingVentMode);
MenuElement mi_venton(&mi_ventpausesmode, &mi_ventpausesmode, "Пауза вкл.");
MenuElementIntSelector mi_ventonperiod(&mi_venton, &mi_venton, "Пер. вкл. (сек.)", 5, 0, 1200, 5, &SwitchedOnVentTime);
MenuElement mi_ventoff(&mi_ventpausesmode, &mi_ventonperiod, "Пауза выкл.");
MenuElementIntSelector mi_ventoffperiod(&mi_ventoff, &mi_ventoff, "Пер. выкл. (сек.)", 5, 0, 1200, 5, &SwitchedOffVentTime);
MenuElement mi_ventheatingmode(&mi_vent, &mi_ventoffperiod, "При нагреве", ChangeVentMode, 2, &dryingVentMode);
MenuElement mi_ventstayonmode(&mi_vent, &mi_ventheatingmode, "При паузе", ChangeVentMode, 3, &dryingVentMode);
MenuElement mi_ventalltimeonmode(&mi_vent, &mi_ventstayonmode, "Всегда вкл.", ChangeVentMode, 4, &dryingVentMode);
MenuElement mi_ventoffmode(&mi_vent, &mi_ventalltimeonmode, "Выкл.", ChangeVentMode, 5, &dryingVentMode);

MenuElement mi_drying_stay_on_delta(&mi_5, &mi_ventoffmode, "Дельта");
MenuElementIntSelector mi_drying_stay_on_delta_vals(&mi_stay_on_delta, &mi_drying_stay_on_delta, "Дельта. (сек.)", 1, 0, 10, 1, &dryingStayOnDelta);


#endif