#include "Control.hpp"
#include "TuneObjectsExt.hpp"
#include <string>
#include "GUI.h"
#include "Lcd_Driver.h"
#include "SocketObjectsExt.hpp"
#include "ScreenObjectsExt.hpp"
#include "SensorObjectsExt.hpp"
#include "NTC_10K_B3950.hpp"


ControlBase::ControlBase(uint16_t id, std::string name, intTune* onOffTune)
	: BaseObject(id, name)
	, OnOffTune(onOffTune)
{
}

ControlBase::ControlBase(std::string name, intTune* onOffTune)
	: BaseObject(name)
	, OnOffTune(onOffTune)
{
}

bool ControlBase::isActive()
{
	return false;
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

void ControlBase::init(uint8_t index)
{
}

SocketsControl::SocketsControl(uint16_t id, 
	std::string name, 
	intTune* onOffTune, 
	IntVectorTune* socketsTune)
	:ControlBase(id, name, onOffTune), 
	SocketsTune()
{
	
	SocketsVector.clear();
	for (auto inItem : BaseUnitSocketsV)
		for (auto tuneval : SocketsTune->val)
			if (tuneval == inItem->_getId())
				SocketsVector.push_back(inItem);
	
}

SocketsControl::SocketsControl(std::string name, 
	intTune* onOffTune, 
	IntVectorTune* socketsTune)
	: ControlBase(id, name, onOffTune)
	, SocketsTune()

{

	SocketsVector.clear();
	for (auto inItem : BaseUnitSocketsV)
		for (auto tuneval : SocketsTune->val)
			if (tuneval == inItem->_getId())
				SocketsVector.push_back(inItem);
	
}

void SocketsControl::SwitchSockets(std::vector< plugSocket*> plugSockets, uint16_t powerVT)
{
}

//sensors sockets control
SensorsSocketsControl::SensorsSocketsControl(
	uint16_t id,
	std::string name,
	intTune* onOffTune,
	IntVectorTune* sensorsTune,
	IntVectorTune* upSocketsTune,
	IntVectorTune* downSocketsTune,
	intTune* timeProfileTune,
	DatePeriodValuesCollection* dpvcollection
	)
	: SocketsControl(id, name, onOffTune, upSocketsTune)
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
	
	SensorsVector.clear();
	for (auto inItem : ADCSensorsV)
		for (auto tuneval : SensorsTune->val)
			if (tuneval == inItem->_getId())
				SensorsVector.push_back(inItem);
	
}

SensorsSocketsControl::SensorsSocketsControl(
	std::string name,
	intTune* onOffTune,
	IntVectorTune* sensorsTune,
	IntVectorTune* upSocketsTune,
	IntVectorTune* downSocketsTune,
	intTune* timeProfileTune,
	DatePeriodValuesCollection* dpvcollection)
	: SocketsControl(name, onOffTune, upSocketsTune)
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
			sum += sens->getSensorUnits(); 
		}
		else
			sum += sens->getSensorUnits(); 
	}
	current_val = sum / SensorsVector.size();
	
	/*if (isActive())
	{
		if (current_val < aim_val - 2) 
		{
			SwitchSockets(DownSocketsVector, 0xffff);
			return;
		}
		if (current_val < aim_val - 1)
		{
			SwitchSockets(DownSocketsVector, 2000);
			return;
		}
		if (current_val < aim_val)
		{
			SwitchSockets(DownSocketsVector, 1000);
			return;
		}if (current_val >= aim_val)
		{
			SwitchSockets(DownSocketsVector, 0);
			return;
		}
	}
	else
	{
		SwitchSockets(DownSocketsVector, 0);
		return;
	}*/

}

void SensorsSocketsControl::FillScreen()
{
	Info_SubHeader.SetText(Name, false);
	Info_FirstString.Set_Prefix_IntVal_Postfix_Text("Текущ.: ", _get_current_val(), 4, CO, true);
	Info_SecondString.Set_Prefix_IntVal_Postfix_Text("Целев.: ", _get_aim_val(), 4, CO, true);
	Info_ThirdString.Set_Prefix_IntVal_Postfix_Text("Нагр.(ВТ): ", 10, 4, "", true);
	Info_FourthString.SetText("****************", false);
	
}


void SensorsSocketsControl::_fillVector(std::vector<BaseObject*> &vectorOut, std::vector<BaseObject*> &vectorIn, IntVectorTune* tune)
{
	
	vectorOut.clear();
	for (auto inItem : vectorIn)
		for (auto tuneval : tune->val)
			if (tuneval == inItem->_getId())
				vectorOut.push_back(inItem);
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

bool SensorsSocketsControl::isActive()
{
	return false;
}





