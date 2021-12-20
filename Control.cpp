#include "Control.hpp"
#include "TuneObjectsExt.hpp"
//#include <string>
#include "GUI.h"
#include "Lcd_Driver.h"
#include "SocketObjectsExt.hpp"
#include "ScreenObjectsExt.hpp"
#include "SensorObjectsExt.hpp"
#include "NTC_10K_B3950.hpp"
#include "Auxiliary.hpp"
#include "TimeProfile.hpp"

ControlBase::ControlBase(uint16_t id, const char* name, intTune* onOffTune, intTune* switchOnMotionPeriodTune)
	: BaseObject(id, name)
	, OnOffTune(onOffTune)
	, SwitchOnMotionPeriodTune(switchOnMotionPeriodTune)
{
}

ControlBase::ControlBase(const char* name, intTune* onOffTune, intTune* switchOnMotionPeriodTune)
	: BaseObject(name)
	, OnOffTune(onOffTune)
	, SwitchOnMotionPeriodTune(switchOnMotionPeriodTune)
{
}

bool ControlBase::isActive()
{
	bool active = true;
	if (delayBeginOnOffTune._getVal() == 1 | delayEndOnOffTune._getVal() == 1)
	{
		RTC_TimeTypeDef sTime = { 0 };
		RTC_DateTypeDef sDate = { 0 };
		HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
		HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
		RTC_TimeTypeDef savedTime = { 0 };
		RTC_DateTypeDef savedDate = { 0 };
		
		if (delayBeginOnOffTune._getVal() == 1)
		{
			savedDate.Date = delayBeginDate._getVal();
			savedDate.Month = delayBeginMonth._getVal();
			savedDate.Year = delayBeginYear._getVal();
		
			savedTime.Hours = delayBeginHour._getVal();
			savedTime.Minutes = delayBeginMinute._getVal();	
			savedTime.Seconds = 0;	
		
			compareRes res = CompareDates(&savedDate, &savedTime, &sDate, &sTime);
			if (res == MORE | res == EQUAL)
				active =  true;
			else
				active =  false;
		
		}
	
		//delay end
		if(delayEndOnOffTune._getVal() == 1)
		{
	
			savedDate.Date = delayEndDate._getVal();
			savedDate.Month = delayEndMonth._getVal();
			savedDate.Year = delayEndYear._getVal();
		
			savedTime.Hours = delayEndHour._getVal();
			savedTime.Minutes = delayEndMinute._getVal();	
			savedTime.Seconds = 0;	
		
			compareRes res = CompareDates(&savedDate, &savedTime, &sDate, &sTime);
			if (res == LESS | res == EQUAL)
				active =  true;
			else
				active =  false;
		
		}
		
	}
	//delay start
	
	
	
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

SocketsControl::SocketsControl(uint16_t id, 
	const char* name, 
	intTune* onOffTune,
	intTune* switchOnMotionPeriodTune,
	IntVectorTune* socketsTune)
	: ControlBase(id, name, onOffTune, switchOnMotionPeriodTune)
	, SocketsTune(socketsTune)
{
}

SocketsControl::SocketsControl(const char* name, 
	intTune* onOffTune, 
	intTune* switchOnMotionPeriodTune,
	IntVectorTune* socketsTune)
	: ControlBase(name, onOffTune, switchOnMotionPeriodTune)
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
	intTune* onOffTune,
	intTune* switchOnMotionPeriodTune,
	IntVectorTune* sensorsTune,
	IntVectorTune* upSocketsTune,
	IntVectorTune* downSocketsTune,
	intTune* timeProfileTune,
	PeriodValuesCollection* dpvcollection)
	: SocketsControl(id, name, onOffTune, switchOnMotionPeriodTune, upSocketsTune)
	, SensorsTune(sensorsTune)
	, DownSocketsTune(downSocketsTune)
	, TimeProfileTune(timeProfileTune)
	, DPVCollection(dpvcollection)
{
}

SensorsSocketsControl::SensorsSocketsControl(
	const char* name,
	intTune* onOffTune,
	intTune* switchOnMotionPeriodTune,
	IntVectorTune* sensorsTune,
	IntVectorTune* upSocketsTune,
	IntVectorTune* downSocketsTune,
	intTune* timeProfileTune,
	PeriodValuesCollection* dpvcollection)
	: SocketsControl(name, onOffTune, switchOnMotionPeriodTune, upSocketsTune)
	, SensorsTune(sensorsTune)
	, DownSocketsTune(downSocketsTune)
	, TimeProfileTune(timeProfileTune)
	, DPVCollection(dpvcollection)
{	
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
	
	_get_aim_val();
	_get_current_val();
	
	if (isActive())
	{
		uint16_t upPower = 0;
		uint16_t downPower = 0;
		
		if (current_val > aim_val) // switch sockets to decriace val
			{
				upPower = 0;
				if (DownSocketsVector.size() > 0)
				{
					if (current_val > aim_val + 2) //cooling max
						{
							downPower = 0xffff;
							SocketsState = DECREASEMAX;
						}
					else if (current_val > aim_val + 1) //cooling 2/3
						{
							downPower = 2000;
							SocketsState = DECREASEMID;
						}
					else if (current_val > aim_val) //cooling  1/3
						{
							downPower = 1000;
							SocketsState = DECREASEMIN;
						}
					else
					{
						downPower = 0;     //stay on
						SocketsState = STAYONAIM;
					}
				}
				else
				{
					downPower = 0;     //stay on
					SocketsState = STAYONAIM;
				}
		}	
		else // switch sockets to increace val
			{
				downPower = 0;
				if (SocketsVector.size() > 0)
				{
					if (current_val < aim_val - 2) 
					{
						upPower = 0xffff;
						SocketsState = INCREASEMAX;
					}
					else if (current_val < aim_val - 1)
					{
						upPower = 2000;
						SocketsState = INCREASEMID;
					}
					else if (current_val < aim_val)
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
			
			if (current_val >= aim_val - DPVCollection->StayOnDeltaTune->_getVal() && 
				current_val <= aim_val + DPVCollection->StayOnDeltaTune->_getVal())
				result = DPVCollection->UpdateCurrentPeriotStateTime(STAYON);
			else if (current_val < aim_val - DPVCollection->StayOnDeltaTune->_getVal())
				result = DPVCollection->UpdateCurrentPeriotStateTime(HEATING);
			else if (current_val > aim_val + DPVCollection->StayOnDeltaTune->_getVal())
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

void SensorsSocketsControl::FillScreen()
{
	
}

uint16_t SensorsSocketsControl::_get_aim_val()
{
	aim_val = DPVCollection->getValue(TimeProfileTune->_getVal());
	return aim_val;
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

void PumpControl::ExecuteStep()
{
	if (isOn())
	{	
		
		
		TimePeriodState currState;
		if (beerModeIndex._getVal() == 0)
			currState = mashingDPVCollection->getCurrentState();
		else
			currState = boilingDPVCollection->getCurrentState();
		
		
		switch (PumpModeTune->_getVal()) 
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
				break;
			}
		}
	}
}

void PumpControl::FillScreen()
{
}

PumpControl::PumpControl(uint16_t id, 
	const char* name, 
	intTune* onOffTune, 
	IntVectorTune* SocketsTune, 
	intTune* pumpModeTune, 
	intTune* periodOnTune, 
	intTune* periodOffTune, 
	PeriodValuesCollection* mashingdpvcollection,
	PeriodValuesCollection* boilingdpvcollection)
	: SocketsControl(name, onOffTune, nullptr, SocketsTune)
	, PumpModeTune(pumpModeTune)
	, PeriodOnTune(periodOnTune)
	, PeriodOffTune(periodOffTune)
	, mashingDPVCollection(mashingdpvcollection)
	, boilingDPVCollection(boilingdpvcollection)
{
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
