#include "Control.hpp"
#include "TuneObjectsExt.hpp"
#include <string>
#include "GUI.h"
#include "Lcd_Driver.h"
#include "SocketObjectsExt.hpp"
#include "ScreenObjectsExt.hpp"
#include "SensorObjectsExt.hpp"
#include "NTC_10K_B3950.hpp"
#include "Auxiliary.h"


ControlBase::ControlBase(uint16_t id, std::string name, intTune* onOffTune, intTune* switchOnMotionPeriodTune)
	: BaseObject(id, name)
	, OnOffTune(onOffTune)
	, SwitchOnMotionPeriodTune(switchOnMotionPeriodTune)
{
}

ControlBase::ControlBase(std::string name, intTune* onOffTune, intTune* switchOnMotionPeriodTune)
	: BaseObject(name)
	, OnOffTune(onOffTune)
	, SwitchOnMotionPeriodTune(switchOnMotionPeriodTune)
{
}

bool ControlBase::isActive()
{
	
	bool active = true;
	
	RTC_TimeTypeDef sTime = { 0 };
	RTC_DateTypeDef sDate = { 0 };
	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

	RTC_TimeTypeDef savedTime = { 0 };
	RTC_DateTypeDef savedDate = { 0 };
	
	//delay start
	
	
	if(delayBeginOnOffTune._getVal() == 1)
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
	return active;
}

void ControlBase::clearLCD()
{
	LCD_DrawFillRectangle(Left_X, Top_Y, Right_X, Bottom_Y, BackColor); 
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
	std::string name, 
	intTune* onOffTune,
	intTune* switchOnMotionPeriodTune,
	IntVectorTune* socketsTune)
	: ControlBase(id, name, onOffTune, switchOnMotionPeriodTune)
	, SocketsTune(socketsTune)
{
	SocketsVector.clear();
	if (SocketsTune != nullptr)
	{
		SocketsVector.clear();
		for (auto inItem : BaseUnitSocketsV)
			for (auto tuneval : SocketsTune->val)
				if (tuneval == inItem->_getId())
					SocketsVector.push_back(inItem);
		
		for (auto sock : SocketsVector)
			sock->SwitchOff();
		
	}
}

SocketsControl::SocketsControl(std::string name, 
	intTune* onOffTune, 
	intTune* switchOnMotionPeriodTune,
	IntVectorTune* socketsTune)
	: ControlBase(id, name, onOffTune, switchOnMotionPeriodTune)
	, SocketsTune(socketsTune)

{	
	SocketsVector.clear();
	if (SocketsTune != nullptr)
	{
		SocketsTune->_getVal();
		for (auto inItem : BaseUnitSocketsV)
			for (auto tuneval : SocketsTune->val)
				if (tuneval == inItem->_getId())
					SocketsVector.push_back(inItem);
		
		for (auto sock : SocketsVector)
			sock->SwitchOff();

	}
}

void SocketsControl::init()
{
}


void SocketsControl::SwitchSockets(uint16_t powerVT)
{
	SwitchToPower(SocketsVector, powerVT);
}

//sensors sockets control
SensorsSocketsControl::SensorsSocketsControl(
	uint16_t id,
	std::string name,
	intTune* onOffTune,
	intTune* switchOnMotionPeriodTune,
	IntVectorTune* sensorsTune,
	IntVectorTune* upSocketsTune,
	IntVectorTune* downSocketsTune,
	intTune* timeProfileTune,
	DatePeriodValuesCollection* dpvcollection)
	: SocketsControl(id, name, onOffTune, switchOnMotionPeriodTune, upSocketsTune)
	, SensorsTune(sensorsTune)
	, DownSocketsTune(downSocketsTune)
	, TimeProfileTune(timeProfileTune)
	, DPVCollection(dpvcollection)
{
	
	DownSocketsVector.clear();
	for (auto inItem : BaseUnitSocketsV)
		for (auto tuneval : DownSocketsTune->val)
			if (tuneval == inItem->_getId())
				DownSocketsVector.push_back(inItem);
	
	for (auto sock : DownSocketsVector)
		sock->SwitchOff();
	
	SensorsVector.clear();
	for (auto inItem : ADCSensorsV)
		for (auto tuneval : SensorsTune->val)
			if (tuneval == inItem->_getId())
				SensorsVector.push_back(inItem);
	
}

SensorsSocketsControl::SensorsSocketsControl(
	std::string name,
	intTune* onOffTune,
	intTune* switchOnMotionPeriodTune,
	IntVectorTune* sensorsTune,
	IntVectorTune* upSocketsTune,
	IntVectorTune* downSocketsTune,
	intTune* timeProfileTune,
	DatePeriodValuesCollection* dpvcollection)
	: SocketsControl(name, onOffTune, switchOnMotionPeriodTune, upSocketsTune)
	, SensorsTune(sensorsTune)
	, DownSocketsTune(downSocketsTune)
	, TimeProfileTune(timeProfileTune)
	, DPVCollection(dpvcollection)
{
	
	
	DownSocketsVector.clear();
	DownSocketsTune->_getVal();
	
	for (auto inItem : BaseUnitSocketsV)
		for (auto tuneval : DownSocketsTune->val)
			if (tuneval == inItem->_getId())
				DownSocketsVector.push_back(inItem);
	
	for (auto sock : DownSocketsVector)
		sock->SwitchOff();
	
	SensorsVector.clear();
	for (auto inItem : ADCSensorsV)
		for (auto tuneval : SensorsTune->val)
			if (tuneval == inItem->_getId())
				SensorsVector.push_back(inItem);
	
}

void SensorsSocketsControl::ExecuteStep()
{
	
	aim_val = DPVCollection->getValue(TimeProfileTune->_getVal());
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
	
	if (isActive())
	{
		uint16_t upPower = 0;
		uint16_t downPower = 0;
		
		if (current_val > aim_val) // switch sockets to decriace val
			{
				upPower = 0;
				if (DownSocketsVector.size() > 0)
				{
					if (current_val > aim_val + 2) 
					{
						downPower = 0xffff;
					}
					else if (current_val > aim_val + 1)
					{
						downPower = 2000;
					}
					else if (current_val > aim_val)
					{
						downPower = 100;
					}
					else
					{
						downPower = 0;
					}
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
					}
					else if (current_val < aim_val - 1)
					{
						upPower = 2000;
					}
					else if (current_val < aim_val)
					{
						upPower = 1000;
					}
					else
					{
						upPower = 0;
					}
				}
			}
		SwitchSockets(upPower);
		SwitchDownSockets(downPower);
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
	return aim_val;
}

uint16_t SensorsSocketsControl::_get_current_val()
{
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
				bool state = socket->getSocketState();
				return;
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
