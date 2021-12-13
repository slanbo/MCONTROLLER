#include "Mode.hpp"
#include "Control.hpp"
//#include "ControlObjectsExt.hpp"
//#include "portable.h"
#include "TuneObjectsExt.hpp"

ModeBase::ModeBase(uint16_t ID, std::string name)
	: BaseObject(ID, name) 
{
}

bool ModeBase::isActive()
{
	return ModeTune->_getVal() == id;
}

//controls mode
ControlsMode::ControlsMode(uint16_t ID, std::string name)
	: ModeBase(ID, name)
{
	
}


bool ControlsMode::isActive()
{
	return true;
}


bool ControlsMode::isOn()
{
	if (modeIndex._getVal() == id)
		return true;
	else
		return false;
}

void ControlsMode::FillScreen()
{
	if (isOn())
	{
		const char blank[2] = { ' ', 0 };
		
		Info_Header->ClearText();
		Info_SubHeader->ClearText();
		Info_FirstString->ClearText();
		Info_SecondString->ClearText();
		Info_ThirdString->ClearText();
		Info_FourthString->ClearText();
	
		Info_Header->SetChars(Name, false);
		Info_Header->FillEndBySpaces();
		Info_Header->_setUpdated(true);
	
		Info_SubHeader->SetChars(controlsVector.at(currentControlIndex)->Name, false);
		Info_SubHeader->FillEndBySpaces();
		Info_SubHeader->_setUpdated(true);
	
		SensorsSocketsControl* sscontrol = (SensorsSocketsControl*)controlsVector.at(currentControlIndex);
		
		char ifirst[] = "Тек.:\0";
		Info_FirstString->SetChars(ifirst, true);
		Info_FirstString->SetIntText(sscontrol->_get_current_val(), 5) ;
		Info_FirstString->SetChars(blank, false);	
		Info_FirstString->SetChars(sscontrol-> GetSensorsUnit(), false);
		Info_FirstString->FillEndBySpaces();
		Info_FirstString->_setUpdated(true);

		char isecond[] = "Цель:\0";
		Info_SecondString->SetChars(isecond, true);
		Info_SecondString->SetIntText(sscontrol->_get_aim_val(), 5);
		Info_SecondString->SetChars(blank, false);
		Info_SecondString->SetChars(sscontrol->GetSensorsUnit(), false);
		Info_SecondString->FillEndBySpaces();
		Info_SecondString->_setUpdated(true);
	
		char ithird[] = "Нагр.:\0";
		Info_ThirdString->SetChars(ithird, true);
		Info_ThirdString->SetIntText(controlsVector.at(currentControlIndex)->GetSocketsPowerVT(), 5);
		Info_ThirdString->SetChars(blank, false);
		char vt[] = "ВТ\0";
		Info_ThirdString->SetChars(vt, true);
		Info_ThirdString->FillEndBySpaces();
		Info_ThirdString->_setUpdated(true);
	
		char ifourth[] = "_____________\0";
		Info_FourthString->SetChars(ifourth, true);
		Info_FourthString->FillEndBySpaces();
		Info_FourthString->_setUpdated(true);
	
		currentControlIndex++;
		if (currentControlIndex == controlsVector.size())
		{
			currentControlIndex = 0;
			allscreensfilled = true;
		}
	}
}

void ControlsMode::ExecuteStep()
{
	if (isOn())
	{
	for(auto e : controlsVector)
		e->ExecuteStep();
	}
}

// habitat

Habitat::Habitat(uint16_t ID, 
	std::string name)
	: ControlsMode(ID, name)
{
	PeriodValuesCollection* airTempDVPC = new PeriodValuesCollection(DATE_PERIOD);
	DatePeriodValue *adpv = new DatePeriodValue(1, "All time", 3, 0, 1, 23, 59, 0, 0, 0, 0, 0, &airFixTemp);
	airTempDVPC->addPeriodValue((PeriodValue*)adpv);
	
	airTempControl = new SensorsSocketsControl
		(
		"Темпер. возд:", 
		&airTempControlOnOffTune,
		&airTempControlSwichOnIfMotionPeriod,
		&airTempControlSensors,
		&airTempControlUpSockets,
		&airTempControlDownSockets,
		&airTempControlTimeProfile,
		airTempDVPC);
	
	
	PeriodValuesCollection* batTempDVPC = new PeriodValuesCollection(DATE_PERIOD);
	DatePeriodValue *bdpv1 = new DatePeriodValue(1, "Night time 1", 0, 0, 1, 6, 59, 0, 0, 0, 0, 0, &batNightFixTemp);
	batTempDVPC->addPeriodValue((PeriodValue*)bdpv1);
	DatePeriodValue *bdpv2 = new DatePeriodValue(2, "Day time", 0, 7, 0, 22, 59, 0, 0, 0, 0, 0, &batDayFixTemp);
	batTempDVPC->addPeriodValue((PeriodValue*)bdpv2);
	DatePeriodValue *bdpv3 = new DatePeriodValue(3, "Night time 2", 0, 23, 0, 23, 59, 0, 0, 0, 0, 0, &batNightFixTemp);
	batTempDVPC->addPeriodValue((PeriodValue*)bdpv3);
	
	
	batTempControl = new SensorsSocketsControl
			(
		"Темпер. бат:", 
		&batTempControlOnOffTune,
		nullptr,
		&batTempControlSensors,
		&batTempControlUpSockets,
		&batTempControlDownSockets,
		&batTempControlTimeProfile,
		batTempDVPC);
	
	PeriodValuesCollection* CODVPC = new PeriodValuesCollection(DATE_PERIOD);
	DatePeriodValue *cdpv = new DatePeriodValue(1, "All day", 0, 0, 1, 6, 59, 0, 0, 0, 0, 0, &CODangerLevel);
	CODVPC->addPeriodValue((PeriodValue*)cdpv);

	coControl = new SensorsSocketsControl
		(
		"Газ:", 
		&coControlOnOffTune,
		&COControlSwichOnIfMotionPeriod,
		&COControlSensors,
		&COControlUpSockets,
		&COControlDownSockets,
		&COControlTimeProfile,
		CODVPC);	
	
	PeriodValuesCollection* lightDVPC = new PeriodValuesCollection(DATE_PERIOD);
	DatePeriodValue *ldpv = new DatePeriodValue(1, "All day", 0, 0, 1, 6, 59, 0, 0, 0, 0, 0, &LightEdge);
	lightDVPC->addPeriodValue((PeriodValue*)ldpv);
	
	lightControl = new SensorsSocketsControl
		(
		"Освещение:", 
		&lightControlOnOffTune,
		&lightControlSwichOnIfMotionPeriod,
		&lightControlSensors,
		&lightControlUpSockets,
		&lightControlDownSockets,
		&lightControlTimeProfile,
		lightDVPC);
	
	controlsVector.push_back(airTempControl);
	controlsVector.push_back(batTempControl);
	controlsVector.push_back(coControl);
	controlsVector.push_back(lightControl);
}

Habitat::~Habitat()
{
	delete airTempControl;
	delete coControl;
	delete lightControl;
}


void ControlsMode::init()
{
	
}

void Habitat::init()
{
	for (auto elem : controlsVector)
	{
		SensorsSocketsControl* control = (SensorsSocketsControl*)elem;
		control->init();
	}
}

BeerPreparing::BeerPreparing(uint16_t ID, 
	std::string name) : ControlsMode(ID, name)
{
	mashingDVPC->addPeriodValue((PeriodValue*)mtp_1);
	mashingDVPC->addPeriodValue((PeriodValue*)mtp_2);
	mashingDVPC->addPeriodValue((PeriodValue*)mtp_3);
	mashingDVPC->addPeriodValue((PeriodValue*)mtp_4);
	mashingDVPC->addPeriodValue((PeriodValue*)mtp_5);
	mashingDVPC->addPeriodValue((PeriodValue*)mtp_6);
	
	mashingControl = new SensorsSocketsControl
		(
		"Паузы:", 
		&MashingOnOffTune,
		nullptr,
		&boilingMashingControlSensors,
		&boilingMashingControlUpSockets,
		&boilingMashingControlDownSockets,
		nullptr,
		mashingDVPC);
	
	boilingTempDVPC->addPeriodValue((PeriodValue*)btp_1);
	boilingTempDVPC->addPeriodValue((PeriodValue*)btp_2);
	boilingTempDVPC->addPeriodValue((PeriodValue*)btp_3);

	
	
	boilingControl = new SensorsSocketsControl
			(
		"Варка:", 
		&batTempControlOnOffTune,
		nullptr,
		&boilingMashingControlSensors,
		&boilingMashingControlUpSockets,
		&boilingMashingControlDownSockets,
		nullptr,
		boilingTempDVPC);
	
	
	pumpControl = new PumpControl(1,
		"Насос",
		&PumpOnOffTune,
		&pumpControlSockets,
		&PumpMode,
		&SwitchedOnPumpTime,
		&SwitchedOffPumpTime,
		mashingDVPC);
	
	controlsVector.push_back(mashingControl);
	controlsVector.push_back(boilingControl);
	controlsVector.push_back(pumpControl);
	
}


void BeerPreparing::init()
{
	for (auto elem : controlsVector)
	{
		SensorsSocketsControl* control = (SensorsSocketsControl*)elem;
		control->init();
	}
}


void BeerPreparing::FillScreen()
{
	if (isOn())
	{
		SensorsSocketsControl* sscontrol = (SensorsSocketsControl*)controlsVector.at(beerModeIndex._getVal());
		TimePeriodValue* currentPeriod = (TimePeriodValue*)sscontrol->DPVCollection->getCurrentPeriod();
		
		const char blank[2] = { ' ', 0 };
		
		Info_Header->ClearText();
		Info_SubHeader->ClearText();
		Info_FirstString->ClearText();
		Info_SecondString->ClearText();
		Info_ThirdString->ClearText();
		Info_FourthString->ClearText();
	
		Info_Header->SetChars(Name, false);
		Info_Header->FillEndBySpaces();
		Info_Header->_setUpdated(true);
	
		Info_SubHeader->SetChars(controlsVector.at(beerModeIndex._getVal())->Name, false);
		Info_SubHeader->FillEndBySpaces();
		Info_SubHeader->_setUpdated(true);
		
		if (currentScreenIndex == 0)
		{
	
			char ifirst[] = "Пауза:\0";
			Info_FirstString->SetChars(ifirst, true);
			Info_FirstString->FillEndBySpaces();
			Info_FirstString->_setUpdated(true);

			char isecond[] = "";
			if (currentPeriod == nullptr)
				Info_SecondString->SetChars("Завершены", true);
			else
			{
				currentPeriod->getPeriodDescription(isecond);
				Info_SecondString->SetChars(isecond, false);
			}
			
			Info_SecondString->FillEndBySpaces();
			Info_SecondString->_setUpdated(true);
	
			char ithird[] = "Выполнено(с.)\0";
			Info_ThirdString->SetChars(ithird, true);
			Info_ThirdString->FillEndBySpaces();
			Info_ThirdString->_setUpdated(true);
	
			char ifourth[] = "";
			if (currentPeriod == nullptr)
				Info_FourthString->SetChars("Завершены", true);
			else
			{
				currentPeriod->getStateDescription(ifourth);
				Info_FourthString->SetChars(ifourth, false);
			}
			Info_FourthString->FillEndBySpaces();
			Info_FourthString->_setUpdated(true);
		}
		else if (currentScreenIndex == 1)
		{
			char ifirst[] = "Тек.:\0";
			Info_FirstString->SetChars(ifirst, true);
			Info_FirstString->SetIntText(sscontrol->_get_current_val(), 5);
			Info_FirstString->SetChars(blank, false);	
			Info_FirstString->SetChars(sscontrol->GetSensorsUnit(), false);
			Info_FirstString->FillEndBySpaces();
			Info_FirstString->_setUpdated(true);

			char isecond[] = "Цель:\0";
			Info_SecondString->SetChars(isecond, true);
			Info_SecondString->SetIntText(sscontrol->_get_aim_val(), 5);
			Info_SecondString->SetChars(blank, false);
			Info_SecondString->SetChars(sscontrol->GetSensorsUnit(), false);
			Info_SecondString->FillEndBySpaces();
			Info_SecondString->_setUpdated(true);
	
			char ithird[] = "Нагр.:\0";
			Info_ThirdString->SetChars(ithird, true);
			Info_ThirdString->SetIntText(controlsVector.at(beerModeIndex._getVal())->GetSocketsPowerVT(), 5);
			Info_ThirdString->SetChars(blank, false);
			char vt[] = "ВТ\0";
			Info_ThirdString->SetChars(vt, true);
			Info_ThirdString->FillEndBySpaces();
			Info_ThirdString->_setUpdated(true);
	
			char ifourth[] = "_____________\0";
			Info_FourthString->SetChars(ifourth, true);
			Info_FourthString->FillEndBySpaces();
			Info_FourthString->_setUpdated(true);
			
		}
		else if (currentScreenIndex == 2)
		{
			char ifirst[] = "Режим насоса:\0";
			Info_FirstString->SetChars(ifirst, true);
			Info_FirstString->FillEndBySpaces();
			Info_FirstString->_setUpdated(true);

			switch (PumpMode._getVal()) 
			{
			case 1: // period on /period off
				{
					Info_SecondString->SetChars("Периодами", true);
							break;
				}
			case 2: // on heating
				{
					Info_SecondString->SetChars("При нагреве", true);
							break;
				}
			case 3: // on stay on
				{
					Info_SecondString->SetChars("При паузе", true);
							break;
				}
			case 4: // alltime on
				{	
					Info_SecondString->SetChars("Все время", true);
							break;
				}	
			default: // alltime on
				{
					Info_SecondString->SetChars("Неопрелено", true);
							break;
				}
			}
			
			
			Info_SecondString->FillEndBySpaces();
			Info_SecondString->_setUpdated(true);
	
			char ithird[] = "Cocт. насоса:\0";
			Info_ThirdString->SetChars(ithird, true);
			Info_ThirdString->FillEndBySpaces();
			Info_ThirdString->_setUpdated(true);
	
			char ifourth[] = "";
			Info_FourthString->SetChars(ifourth, true);
			Info_FourthString->FillEndBySpaces();
			Info_FourthString->_setUpdated(true);
		}

	
		currentScreenIndex++;
		if (currentScreenIndex == BEER_PREPARING_SCREEN_QUANT)
		{
			currentScreenIndex = 0;
			allscreensfilled = true;
		}
	}
}


void BeerPreparing::ExecuteStep()
{
	if (isOn())
	{
		controlsVector.at(beerModeIndex._getVal())->ExecuteStep();
		controlsVector.at(2)->ExecuteStep();
	}
}
