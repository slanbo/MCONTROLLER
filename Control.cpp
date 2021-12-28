#include "Control.hpp"
#include "TuneObjectsExt.hpp"
#include "GUI.h"
#include "Lcd_Driver.h"
#include "SocketObjectsExt.hpp"
#include "ScreenObjectsExt.hpp"
#include "SensorObjectsExt.hpp"
#include "NTC_10K_B3950.hpp"
#include "Auxiliary.hpp"
#include "TimeProfile.hpp"
#include "DelayDateObjectsExt.hpp"
#include "UsartObjectsExt.hpp"
#include "usart.h"

extern SemaphoreHandle_t usart_handle;


ControlBase::ControlBase(
	uint16_t id,
	const char* name,
	const char* uid,
	intTune* onOffTune,
	intTune* switchOnMotionPeriodTune)
	: BaseObject(id, name)
	, OnOffTune(onOffTune)
	, SwitchOnMotionPeriodTune(switchOnMotionPeriodTune)
{
	for (int i = 0; i < MAX_UID_LENGHT - 1; i++)
	{
		UID[i] = *uid;
		if (*uid == 0)
			break;
		uid++;
	}
	UID[MAX_UID_LENGHT - 1] = 0;
}

ControlBase::ControlBase(
	const char* name,
	const char* uid,
	intTune* onOffTune,
	intTune* switchOnMotionPeriodTune)
	: BaseObject(name)
	, OnOffTune(onOffTune)
	, SwitchOnMotionPeriodTune(switchOnMotionPeriodTune)
{
	for (int i = 0; i < MAX_UID_LENGHT - 1; i++)
	{
		UID[i] = *uid;
		if (*uid == 0)
			break;
		uid++;
	}
	UID[MAX_UID_LENGHT - 1] = 0;
	
}

bool ControlBase::isActive()
{
	bool active = true;
	
	
	if (delayBegin->isOn())
		active = delayBegin->isActive();
	
	if (active & delayEnd->isOn())
		active = delayEnd->isActive();
	
	
	//motion detection 
	if(OnOffTune->_getVal() == 2)
	{
		if (SwitchOnMotionPeriodTune != nullptr & SwitchOnMotionPeriodTune->_getVal() > 0)
		{
			uint16_t motions = IRMSensor->motionsDetected(SwitchOnMotionPeriodTune->_getVal());
			if (motions > 0)
				active =  true;
			else 
				active =  false;
		}
		else
		{
			active =  true;
		}
	}
	else if(OnOffTune->_getVal() == 0)
		active =  false;
	
	return active;
}


bool ControlBase::isOn()
{
	if (OnOffTune->_getVal() == 1)
	{
		return true;
	}
	return false;
}

void ControlBase::init()
{
}

SocketsControl::SocketsControl(
	uint16_t id, 
	const char* name, 
	const char* uid,
	intTune* onOffTune,
	intTune* switchOnMotionPeriodTune,
	IntVectorTune* socketsTune)
	: ControlBase(id, name, uid, onOffTune, switchOnMotionPeriodTune)
	, SocketsTune(socketsTune)
{
}

SocketsControl::SocketsControl(
	const char* name, 
	const char* uid,
	intTune* onOffTune, 
	intTune* switchOnMotionPeriodTune,
	IntVectorTune* socketsTune)
	: ControlBase(name, uid, onOffTune, switchOnMotionPeriodTune)
	, SocketsTune(socketsTune)

{	
}

void SocketsControl::init()
{
	SocketsVector.clear();
	if (SocketsTune != nullptr)
	{
		SocketsTune->restore();
		SocketsTune->_getVal();
		for (auto inItem : BaseUnitSocketsV)
			for (auto tuneval : SocketsTune->val)
				if (tuneval == inItem->_getId())
					SocketsVector.push_back(inItem);
		for (auto sock : SocketsVector)
			sock->SwitchOff();
	}
}


void SocketsControl::SwitchSockets(uint16_t powerVT)
{
	SwitchToPower(SocketsVector, powerVT);
}

//sensors sockets control
SensorsSocketsControl::SensorsSocketsControl(
	uint16_t id,
	const char* name,
	const char* uid,
	intTune* onOffTune,
	intTune* switchOnMotionPeriodTune,
	IntVectorTune* sensorsTune,
	IntVectorTune* upSocketsTune,
	IntVectorTune* downSocketsTune,
	intTune* timeProfileTune,
	PeriodValuesCollection* dpvcollection)
	: SocketsControl(id, name, uid, onOffTune, switchOnMotionPeriodTune, upSocketsTune)
	, SensorsTune(sensorsTune)
	, DownSocketsTune(downSocketsTune)
	, TimeProfileTune(timeProfileTune)
	, DPVCollection(dpvcollection)
{
	if (DPVCollection->Type == TIME_PERIOD)
		screensQuant = 2;
}

SensorsSocketsControl::SensorsSocketsControl(
	const char* name,
	const char* uid,
	intTune* onOffTune,
	intTune* switchOnMotionPeriodTune,
	IntVectorTune* sensorsTune,
	IntVectorTune* upSocketsTune,
	IntVectorTune* downSocketsTune,
	intTune* timeProfileTune,
	PeriodValuesCollection* dpvcollection)
	: SocketsControl(name, uid, onOffTune, switchOnMotionPeriodTune, upSocketsTune)
	, SensorsTune(sensorsTune)
	, DownSocketsTune(downSocketsTune)
	, TimeProfileTune(timeProfileTune)
	, DPVCollection(dpvcollection)
{	
	if (DPVCollection->Type == TIME_PERIOD)
	screensQuant = 2;
}

void SensorsSocketsControl::init()
{
	SocketsControl::init();	
	DownSocketsTune->restore();
	DownSocketsVector.clear();
	for (auto inItem : BaseUnitSocketsV)
		for (auto tuneval : DownSocketsTune->val)
			if (tuneval == inItem->_getId())
				DownSocketsVector.push_back(inItem);
	
	for (auto sock : DownSocketsVector)
		sock->SwitchOff();
	
	
	SensorsTune->restore();
	SensorsVector.clear();
	for (auto inItem : ADCSensorsV)
		for (auto tuneval : SensorsTune->val)
			if (tuneval == inItem->_getId())
				SensorsVector.push_back(inItem);
}



void SensorsSocketsControl::ExecuteStep()
{
	
	_get_low_aim_val();
	_get_high_aim_val();
	_get_current_val();
	
	if (isActive())
	{
		uint16_t upPower = 0;
		uint16_t downPower = 0;
		
		if (current_val > high_aim_val) // switch sockets to decriace val
			{
				upPower = 0;
				if (DownSocketsVector.size() > 0)
				{
					if (current_val > high_aim_val + 2) //cooling max
						{
							downPower = 0xffff;
							SocketsState = DECREASEMAX;
						}
					else if (current_val > high_aim_val + 1) //cooling 2/3
						{
							downPower = 2000;
							SocketsState = DECREASEMID;
						}
					else if (current_val > high_aim_val) //cooling  1/3
						{
							downPower = 1000;
							SocketsState = DECREASEMIN;
						}
					else
					{
						downPower = 0;      //stay on
						SocketsState = STAYONAIM;
					}
				}
				else
				{
					downPower = 0;      //stay on
					SocketsState = STAYONAIM;
				}
			}	
		else // switch sockets to increace val
			{
				downPower = 0;
				if (SocketsVector.size() > 0)
				{
					if (current_val < low_aim_val - 2) 
					{
						upPower = 0xffff;
						SocketsState = INCREASEMAX;
					}
					else if (current_val < low_aim_val - 1)
					{
						upPower = 2000;
						SocketsState = INCREASEMID;
					}
					else if (current_val < low_aim_val)
					{
						upPower = 1000;
						SocketsState = INCREASEMIN;
					}
					else
					{
						upPower = 0;
						SocketsState = STAYONAIM;
					}
				}
			}
		SwitchSockets(upPower);
		SwitchDownSockets(downPower);
		
		if (DPVCollection->Type == TIME_PERIOD)
		{
			bool result = false;
			
			if (current_val >= low_aim_val - DPVCollection->StayOnDeltaTune->_getVal() && 
				current_val <= low_aim_val + DPVCollection->StayOnDeltaTune->_getVal())
				result = DPVCollection->UpdateCurrentPeriotStateTime(STAYON);
			else if (current_val < low_aim_val - DPVCollection->StayOnDeltaTune->_getVal())
				result = DPVCollection->UpdateCurrentPeriotStateTime(HEATING);
			else if (current_val > low_aim_val + DPVCollection->StayOnDeltaTune->_getVal())
				result = DPVCollection->UpdateCurrentPeriotStateTime(COOLING);
						
			
			if (!result)
			{
				OnOffTune->_setVal(0);
				OnOffTune->save();
			}
		}
	}
	else
	{
		SwitchSockets(0);
		SwitchDownSockets(0);
	}
}

void SensorsSocketsControl::FillScreen(uint8_t snum)
{
	const char blank[2] = { ' ', 0 };
	
	Info_SubHeader->ClearText();
	Info_FirstString->ClearText();
	Info_SecondString->ClearText();
	Info_ThirdString->ClearText();
	Info_FourthString->ClearText();
	
	if (snum == 1)
	{
		Info_SubHeader->SetChars(Name, false);
		if (isOn())
			Info_SubHeader->SetChars(" +", true);
		else
			Info_SubHeader->SetChars(" -", true);
		
		Info_SubHeader->FillEndBySpaces();
		Info_SubHeader->_setUpdated(true);
	
		Info_FirstString->SetChars("Текушая: \0", true);
		Info_FirstString->SetIntText(_get_current_val(), 0);
		Info_FirstString->SetChars(blank, false);	
		Info_FirstString->SetChars(GetSensorsUnit(), false);
		Info_FirstString->FillEndBySpaces();
		Info_FirstString->_setUpdated(true);

		Info_SecondString->SetChars("Целевая: \0", true);
		Info_SecondString->SetIntText(_get_low_aim_val(), 0);
		Info_SecondString->SetChars("-", false);
		Info_SecondString->SetIntText(_get_high_aim_val(), 0);
		Info_SecondString->SetChars(blank, false);	
		Info_SecondString->SetChars(GetSensorsUnit(), false);
		Info_SecondString->FillEndBySpaces();
		Info_SecondString->_setUpdated(true);
	
		Info_ThirdString->SetChars("Нагр. + : \0", true);
		Info_ThirdString->SetIntText(GetSocketsPowerVT(), 0);
		Info_ThirdString->SetChars(blank, false);
		Info_ThirdString->SetChars("ВТ\0", true);
		Info_ThirdString->FillEndBySpaces();
		Info_ThirdString->_setUpdated(true);
	
		Info_FourthString->SetChars("Нагр. - : \0", true);
		Info_FourthString->SetIntText(GetDownSocketsPowerVT(), 0);
		Info_FourthString->SetChars(blank, false);
		Info_FourthString->SetChars("ВТ\0", true);
		Info_FourthString->FillEndBySpaces();
		Info_FourthString->_setUpdated(true);
	}
	else if (snum == 2)
	{
		if (DPVCollection->Type == TIME_PERIOD)
		{
			Info_FirstString->SetChars("Пауза:\0", true);
			Info_FirstString->FillEndBySpaces();
			Info_FirstString->_setUpdated(true);
			char strstate[] = "";
			char strperiod[] = "";
			
			uint8_t currtpindex = DPVCollection->getCurrentPeriodIndex();
			
			uint16_t periodTime = 0;
			uint16_t periodTemp = 0;
			uint16_t StayOnTime = 0;
			
			if (currtpindex != 0xff)
			{
				TimePeriodValue* tpValue = (TimePeriodValue*)DPVCollection->PeriodValues.at(currtpindex);
				periodTime = tpValue->TimeTune->_getVal();
				periodTemp = tpValue->_getLowLevelTune()->_getVal();
				StayOnTime = tpValue->getStayOnTime();
			}
			
			if (currtpindex == 0xff)
				Info_SecondString->SetChars("Завершены\0", true);
			else
			{
				char CO[3] = { 67, 176, 0 };
	
				Info_SecondString->SetIntText(periodTemp, 0);
				Info_SecondString->SetChars(" ", false);
				Info_SecondString->SetChars(CO, false);
				Info_SecondString->SetChars(" ", false);
				Info_SecondString->SetIntText(periodTime, 0);
				Info_SecondString->SetChars(" сек.", true);
			}
			
			Info_SecondString->FillEndBySpaces();
			Info_SecondString->_setUpdated(true);
	
			Info_ThirdString->SetChars("Выполнено(сек.)\0", true);
			Info_ThirdString->FillEndBySpaces();
			Info_ThirdString->_setUpdated(true);

			if (currtpindex == 0xff)
				Info_FourthString->SetChars("Завершены", true);
			else
			{
				Info_FourthString->SetIntText(StayOnTime, 0);
				Info_FourthString->SetChars(" из ", true);
				Info_FourthString->SetIntText(periodTime, 0);
				
			}
			
			Info_FourthString->FillEndBySpaces();
			Info_FourthString->_setUpdated(true);
		}
	}
}

uint16_t SensorsSocketsControl::_get_low_aim_val()
{
	low_aim_val = DPVCollection->getValue(LOW_LEVEL ,TimeProfileTune->_getVal());
	return low_aim_val;
}

uint16_t SensorsSocketsControl::_get_high_aim_val()
{
	high_aim_val = DPVCollection->getValue(HIGH_LEVEL, TimeProfileTune->_getVal());
	return high_aim_val;
}

uint16_t SensorsSocketsControl::_get_current_val()
{
	uint16_t sum = 0;
	for (auto sens : SensorsVector)
	{
		if (sens->sensorTypeIndex == TERMISTOR_TYPE_INDEX)
		{
			NTC_10K_B3950* termistorptr = (NTC_10K_B3950*)sens;
			sum += termistorptr->getSensorUnits(); 
		}
		if (sens->sensorTypeIndex == CO_SENSOR_TYPE_INDEX)
		{
			MQ7* cosensptr = (MQ7*)sens;
			sum += cosensptr->getSensorUnits(); 
		}
		if (sens->sensorTypeIndex == LIGHT_SENSOR_TYPE_INDEX)
		{
			LightSensor* lightsensptr = (LightSensor*)sens;
			sum += lightsensptr->getSensorUnits(); 
		}
	}
	current_val = sum / SensorsVector.size();
	return current_val;
}


void SensorsSocketsControl::_set_aim_val(uint16_t val)
{
}

void SensorsSocketsControl::_set_current_val(uint16_t val)
{
}

char* SensorsSocketsControl::GetSensorsUnit()
{
	return SensorsVector.at(0)->UNITS;
}


SensorsSocketsControl::~SensorsSocketsControl()
{
}

SensorsSocketsControl::SensorsSocketsControl()
{
}


void SensorsSocketsControl::SwitchDownSockets(uint16_t powerVT) 
{
	SwitchToPower(DownSocketsVector, powerVT);
}

SocketsControl::SocketsControl()
{
}


ControlBase::ControlBase()
{
}


void SocketsControl::SwitchToPower(std::vector< plugSocket*> &sockets, uint16_t powerVT)
{
	uint8_t EqualSocketId = 0;
	uint16_t PowerSum = 0;
	bool switched = false;
	
	if (sockets.size() > 0)
	{
		if (powerVT == 0)
			for (auto socket : sockets)
			{
				socket->SwitchOff();
			}
		else
		{
			// find first equal
			for(auto socket : sockets) 
			{
				if (socket->getLoadpowerVT() == powerVT)
					EqualSocketId = socket->_getId();
			}
		
			if (EqualSocketId > 0)
			{
				for (auto socket : sockets) 
				{
					if (EqualSocketId == socket->_getId())
						socket->SwitchOn();
					else
						socket->SwitchOff();
				}
				return;
			}
			
			// switch near
			for(auto socket : sockets) 
			{
				PowerSum = PowerSum + socket->getLoadpowerVT();
				if (PowerSum < powerVT)
				{
					socket->SwitchOn();
					switched = true;
				}
				else
					socket->SwitchOff();
			}
			if (!switched)
				for (uint8_t i = 0; i < sockets.size(); i++)
				{
					if (i == 0)
						sockets.at(i)->SwitchOn();	
					else
						sockets.at(i)->SwitchOff();	
				}
		}
	}
}

uint16_t SocketsControl::GetSocketsPowerVT()
{
	uint16_t sum = 0;
	
	for (auto sock : SocketsVector)
		if (sock->getSocketState())
			sum = sum + sock->getLoadpowerVT();
	return sum;
}

void MixControl::ExecuteStep()
{
	if (isOn())
	{	
		TimePeriodState currState;
		currState = DPVCollection->getCurrentState();
		
		
		switch (ModeTune->_getVal()) 
		{
		case 1: // period on /period off
			{
				if (currState != STAYON & currState != HEATING & currState != COOLING)
				{
					SwitchSockets(0);
					break;
				}
				
				bool swichedon = false;
				
				for (auto s : SocketsVector) 
					if (s->getSocketState())
						swichedon = true;
				
				time_t currSeconds = getCurrentSecondsFromBegin();
				if (swichedSeconds == 0)
				{
					SwitchSockets(0xffff);
					swichedSeconds = currSeconds;
				}
				else
				{
					if (swichedon)
					{
						if (currSeconds - swichedSeconds > PeriodOnTune->_getVal())
						{
							SwitchSockets(0);
							swichedSeconds = currSeconds;
						}
					}
					else
					{
						if (currSeconds - swichedSeconds > PeriodOffTune->_getVal())
						{
							SwitchSockets(0xffff);
							swichedSeconds = currSeconds;
						}
					}
				}
				
				break;
			}
		case 2: // on heating
			{
				if (currState == HEATING)
					SwitchSockets(0xffff);
				else
					SwitchSockets(0);
				break;
			}
		case 3: // on stay on
			{
				if (currState == STAYON)
					SwitchSockets(0xffff);
				else
					SwitchSockets(0);				
				break;
			}
		case 4: // alltime on
			{
				if (currState == STAYON | currState == HEATING | currState == COOLING)
					SwitchSockets(0xffff);
				else
					SwitchSockets(0);				
				break;
			}	
		default: // alltime on
			{
				if (currState == STAYON | currState == HEATING | currState == COOLING)
					SwitchSockets(0xffff);
				else
					SwitchSockets(0);				
				break;
			}
		}
	}
}

void MixControl::FillScreen(uint8_t snum)
{
	Info_SubHeader->ClearText();
	Info_FirstString->ClearText();
	Info_SecondString->ClearText();
	Info_ThirdString->ClearText();
	Info_FourthString->ClearText();

	
	Info_SubHeader->SetChars(Name, false);
	if (isOn())
		Info_SubHeader->SetChars(" +", true);
	else
		Info_SubHeader->SetChars(" -", true);
		
	Info_SubHeader->FillEndBySpaces();
	Info_SubHeader->_setUpdated(true);
			
	Info_FirstString->SetChars("Режим:\0", true);
	Info_FirstString->FillEndBySpaces();
	Info_FirstString->_setUpdated(true);

	switch (ModeTune->_getVal()) 
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
	
	Info_ThirdString->SetChars("Cocтояние:\0", true);
	Info_ThirdString->FillEndBySpaces();
	Info_ThirdString->_setUpdated(true);
	
	if (GetSocketsPowerVT() > 0) 
		Info_FourthString->SetChars("Включен", true);
	else				
		Info_FourthString->SetChars("Выключен", true);
	Info_FourthString->FillEndBySpaces();
	Info_FourthString->_setUpdated(true);
}

MixControl::MixControl(uint16_t id, 
	const char* name, 
	const char* uid,
	intTune* onOffTune, 
	IntVectorTune* SocketsTune, 
	intTune* modeTune, 
	intTune* periodOnTune, 
	intTune* periodOffTune, 
	PeriodValuesCollection* dpvcollection)
	: SocketsControl(name, uid, onOffTune, nullptr, SocketsTune)
	, ModeTune(modeTune)
	, PeriodOnTune(periodOnTune)
	, PeriodOffTune(periodOffTune)
{
	screensQuant = 1;
}


uint16_t SensorsSocketsControl::GetDownSocketsPowerVT()
{
	uint16_t sum = 0;
	
	for (auto sock : DownSocketsVector)
		if (sock->getSocketState())
			sum = sum + sock->getLoadpowerVT();
	return sum;
	
}


void ControlBase::setOn(bool state)
{
	if (state)
		OnOffTune->_setVal(1);
	else
		OnOffTune->_setVal(0);
}


uint8_t ControlBase::getScreensQuant()
{
	return screensQuant;
}

void ControlBase::GetUsartMessage(uint8_t messagenum, uint8_t* data, uint16_t lenght)
{
	
	switch (messagenum)
	{
	case 1:
		{
			uint8_t i = 0; uint8_t j = 0;
			char MessageType[] = "CONTROL_NAME_\0";
			while (MessageType[i] != 0){data[i] = MessageType[i]; i++; }
			while (Name[j] != 0){data[i + j] = Name[j]; j++; }
			data[i + j] = 0;
			lenght = i + j;
			break;
		}
		
	default:
		{
			
		}
	}
	

}
