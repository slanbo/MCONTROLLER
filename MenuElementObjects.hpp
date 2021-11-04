#include "MenuElement.hpp"
#include "MenuElements.hpp"
#include "IRMotionSensor.h"

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
MenuElementIntSelector mi_8(&mi_7, &mi_7, "Знач. даты", 1, 1, 31, 1, &dateTune, setDate);

MenuElement mi_9(&mi_1, &mi_8, "Месяц");
MenuElementIntSelector mi_10(&mi_9, &mi_9, "Знач. месяца", 1, 1, 12, 1, &monthTune, setMonth);
	
MenuElement mi_11(&mi_1, &mi_10, "Год");
MenuElementIntSelector mi_12(&mi_11, &mi_11, "Знач. года", 2021, 2021, 2031, 1, &yearTune, setYear);
	
MenuElement mi_13(&mi_1, &mi_12, "Час");
MenuElementIntSelector mi_14(&mi_13, &mi_13, "Знач. часа", 0, 0, 24, 1, &hourTune, setHour);

MenuElement mi_15(&mi_1, &mi_14, "Минута");
MenuElementIntSelector mi_16(&mi_15, &mi_15, "Знач. минуты", 1, 1, 60, 1, &minuteTune, setMinute);
	
MenuElement mi_17(&mi_1, &mi_16, "День недели");
MenuElementIntSelector mi_18(&mi_17, &mi_17, "Знач. дня недели", 1, 1, 7, 1, &weekDayTune, setWeekDay);
	
//настройки
MenuElement mi_19(&mi_2, &mi_18, "Восст. умолч.", setDefaults);
		
MenuElement mi_20(&mi_2, &mi_19, "Обнулить счетч.", clearCounters);
	
MenuElement mi_21(&mi_2, &mi_20, "Разъемы");
	
//разъемы
MenuElement mi_22(&mi_21, &mi_21, "Верхняя розетка");
MenuElementIntSelector mi_23(&mi_22, &mi_22, "Подключ. мощн.", 1, 0, 9000, 100, &upSocketLoadPower, setUpSocketLoadPower);

MenuElement mi_24(&mi_21, &mi_23, "Разъем 12 вольт");
MenuElementIntSelector mi_25(&mi_24, &mi_24, "Подключ. мощн.", 1, 0, 1000, 1, &v12LoadPower, setV12SocketLoadPower);

MenuElement mi_26(&mi_21, &mi_25, "Нижняя розетка");
MenuElementIntSelector mi_27(&mi_26, &mi_26, "Подключ. мощн.", 1, 0, 9000, 100, &downSocketLoadPower, setDownSocketLoadPower);
	
//Контроль среды
MenuElement mi_28(&mi_3, &mi_27, "Температ. возд.");
MenuElement mi_29(&mi_3, &mi_28, "Температ. бат.");
MenuElement mi_30(&mi_3, &mi_29, "Угарный газ");
MenuElement mi_31(&mi_3, &mi_30, "Освещенность");

//"Температ. возд."
MenuElement mi_32(&mi_28, &mi_31, "Фиксированная t", 3, &airTempProfileIndex);
MenuElementIntSelector mi_33(&mi_32, &mi_32, "Знач. температуры", 0, 0, 35, 1, &airFixTemp);
	
MenuElement mi_34(&mi_28, &mi_33, "Присутствие", 0, &airTempProfileIndex);
MenuElement mi_35(&mi_28, &mi_34, "Отсутствие", 1, &airTempProfileIndex);
MenuElement mi_36(&mi_28, &mi_35, "Выходные вт. пт.", 2, &airTempProfileIndex);

MenuElement mi_37(&mi_28, &mi_36, "Вкл./Выкл");
MenuElement mi_38(&mi_37, &mi_37, "Включить", 1, &airTempControlOnOffTune);
MenuElement mi_39(&mi_37, &mi_38, "Выключить", 0, &airTempControlOnOffTune);

//MenuElement mi_40(&mi_37, &mi_39, "Вкл. по движ.", 2, &airTempControlOnOffTune);
//MenuElement mi_41(&mi_40, &mi_40, "Анализ за мин.", 1, 0, IR_MOTION_BUFFER_SIZE, 60, &airTempOnIfMotionPeriod);
	
//"Температ. бат."
MenuElement mi_42(&mi_29, &mi_39, "Ночь нагр. до 80", 0, &batTempProfileIndex);
MenuElementIntSelector mi_43(&mi_42, &mi_42, "Знач. фикс. темп.", 1, 0, 100, 1, &batFixTemp);

MenuElement mi_44(&mi_29, &mi_43, "Вкл->/Выкл");
MenuElement mi_45(&mi_44, &mi_44, "Включить", 1, &batTempControlOnOffTune);
MenuElement mi_46(&mi_44, &mi_45, "Выключить", 0, &batTempControlOnOffTune);

	
//"Угарный газ"
MenuElement mi_47(&mi_30, &mi_46, "Ноль. уров. CO");
MenuElementIntSelector mi_48(&mi_47, &mi_47, "Ноль. уров. CO", 300, 300, 1500, 10, &CONullLevel);
	
MenuElement mi_49(&mi_30, &mi_48, "Вкл./Выкл");
MenuElement mi_50(&mi_49, &mi_49, "Включить", 1, &coControlOnOffTune);
MenuElement mi_51(&mi_49, &mi_50, "Выключить", 0, &coControlOnOffTune);
	
//"Освещенность"
MenuElement mi_52(&mi_31, &mi_51, "Ночь выключено.", 0, &LightProfileIndex);
MenuElementIntSelector mi_53(&mi_52, &mi_52, "Порог выключения", 1, 0, 4065, 5, &LightEdge);

MenuElement mi_54(&mi_31, &mi_53, "Всегда включено", 1, &LightProfileIndex);
MenuElementIntSelector mi_55(&mi_54, &mi_54, "Порог выключения", 1, 0, 4065, 5, &LightEdge);

MenuElement mi_56(&mi_31, &mi_55, "Задержка выключения");
MenuElementIntSelector mi_57(&mi_56, &mi_56, "Знач. задерж. сек.", 1, 0, 3600, 60, &LightSwitchOffDelay);

MenuElement mi_58(&mi_31, &mi_57, "Вкл./Выкл");
MenuElement mi_59(&mi_58, &mi_58, "Включить", 1, &lightControlOnOffTune);
MenuElement mi_60(&mi_58, &mi_59, "Выключить", 0, &lightControlOnOffTune);
	
//MenuElement mi_61(&mi_37, &mi_60, "Вкл. по движ.", 2, &lightControlOnOffTune);
//MenuElement mi_62(&mi_61, &mi_61, "Анализ за мин.", 2, 0, IR_MOTION_BUFFER_SIZE, 1, &lightOnIfMotionPeriod);

//приготовление пива
//mashing
MenuElement mi_63(&mi_4, &mi_60, "Температ. паузы", 0, &beerModeIndex);
	
//mashing Pause 1
MenuElement mi_64(&mi_63, &mi_63, "Пауза 1");
MenuElement mi_65(&mi_64, &mi_64, "П1 темп.");
MenuElementIntSelector mi_66(&mi_65, &mi_65, "П1 температ.", 1, 0, 100, 5, &mashingPause1Temp);
MenuElement mi_67(&mi_64, &mi_66, "П1 время");
MenuElementIntSelector mi_68(&mi_67, &mi_67, "П1 время", 1, 0, 720, 5, &mashingPause1Time);

//mashing Pause 2
MenuElement mi_69(&mi_63, &mi_68, "Пауза 2");
MenuElement mi_70(&mi_69, &mi_69, "П2 темп.");
MenuElementIntSelector mi_71(&mi_70, &mi_70, "П2 температ.", 1, 0, 100, 5, &mashingPause2Temp);
MenuElement mi_72(&mi_69, &mi_71, "П2 время");
MenuElementIntSelector mi_73(&mi_72, &mi_72, "П2 время", 1, 0, 720, 5, &mashingPause2Time);

//mashing Pause 3
MenuElement mi_74(&mi_63, &mi_73, "Пауза 3");
MenuElement mi_75(&mi_74, &mi_74, "П3 темп.");
MenuElementIntSelector mi_76(&mi_75, &mi_75, "П3 температ.", 1, 0, 100, 5, &mashingPause3Temp);
MenuElement mi_77(&mi_74, &mi_76, "П3 время");
MenuElementIntSelector mi_78(&mi_77, &mi_77, "П3 время", 1, 0, 720, 5, &mashingPause3Time);

//mashing Pause 4
MenuElement mi_79(&mi_63, &mi_78, "Пауза 4");
MenuElement mi_80(&mi_79, &mi_79, "П4 темп.");
MenuElementIntSelector mi_81(&mi_80, &mi_80, "П4 температ.", 1, 0, 100, 5, &mashingPause4Temp);
MenuElement mi_82(&mi_79, &mi_81, "П4 время");
MenuElementIntSelector mi_83(&mi_82, &mi_82, "П4 время", 1, 0, 720, 5, &mashingPause4Time);

//mashing Pause 5
MenuElement mi_84(&mi_63, &mi_83, "Пауза 5");
MenuElement mi_85(&mi_84, &mi_84, "П5 темп.");
MenuElementIntSelector mi_86(&mi_85, &mi_85, "П5 температ.", 1, 0, 100, 5, &mashingPause5Temp);
MenuElement mi_87(&mi_84, &mi_86, "П5 время");
MenuElementIntSelector mi_88(&mi_87, &mi_87, "П5 время", 1, 0, 720, 5, &mashingPause5Time);

//mashing Pause 6
MenuElement mi_89(&mi_63, &mi_88, "Пауза 6");
MenuElement mi_90(&mi_89, &mi_89, "П6 темп.");
MenuElementIntSelector mi_91(&mi_90, &mi_90, "П6 температ.", 1, 0, 100, 5, &mashingPause6Temp);
MenuElement mi_92(&mi_89, &mi_91, "П6 время");
MenuElementIntSelector mi_93(&mi_92, &mi_92, "П5 время", 1, 0, 720, 5, &mashingPause6Time);
	
//контроль сушки
	
MenuElement mi_94(&mi_4, &mi_93, "Варка", 1, &beerModeIndex);

//boiling Pause 1
MenuElement mi_95(&mi_94, &mi_94, "Пауза 1");
MenuElement mi_96(&mi_95, &mi_95, "П1 темп.");
MenuElementIntSelector mi_97(&mi_96, &mi_96, "П1 температ.", 1, 0, 100, 5, &boilingPause1Temp);
MenuElement mi_98(&mi_95, &mi_97, "П1 время");
MenuElementIntSelector mi_99(&mi_98, &mi_98, "П1 время", 1, 0, 720, 5, &boilingPause1Time);

//boiling Pause 2
MenuElement mi_100(&mi_94, &mi_99, "Пауза 2");
MenuElement mi_101(&mi_100, &mi_100, "П2 темп.");
MenuElementIntSelector mi_102(&mi_101, &mi_101, "П2 температ.", 1, 0, 100, 5, &boilingPause2Temp);
MenuElement mi_103(&mi_100, &mi_102, "П2 время");
MenuElementIntSelector mi_104(&mi_103, &mi_103, "П2 время", 1, 0, 720, 5, &boilingPause2Time);

//boiling Pause 3
MenuElement mi_105(&mi_94, &mi_104, "Пауза 3");
MenuElement mi_106(&mi_105, &mi_105, "П3 темп.");
MenuElementIntSelector mi_107(&mi_106, &mi_106, "П3 температ.", 1, 0, 100, 5, &boilingPause3Temp);
MenuElement mi_108(&mi_105, &mi_107, "П3 время");
MenuElementIntSelector mi_109(&mi_108, &mi_108, "П3 время", 1, 0, 720, 5, &boilingPause3Time);
	
//отложенный старт
MenuElement mi_110(nullptr, &mi_109, "Отлож. старт");
	
//дата начала 
MenuElement mi_111(&mi_110, &mi_110, "Дата старт");
	
MenuElement mi_112(&mi_111, &mi_111, "Год");
MenuElementIntSelector mi_113(&mi_112, &mi_112, "Знач. года", 2021, 2021, 2031, 1, &delayBeginYear);
	
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
MenuElement mi_126(&mi_125, &mi_125, "Дата стоп");
	
MenuElement mi_127(&mi_126, &mi_126, "Год");
MenuElementIntSelector mi_128(&mi_127, &mi_127, "Знач. года", 2021, 2021, 2031, 1, &delayEndYear);
	
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
MenuElementIntSelector mi_179(&mi_178, &mi_178, "Время сек.", 2, 0, IR_MOTION_BUFFER_SIZE, 1, &longPeriodOnIfMotionPeriod);