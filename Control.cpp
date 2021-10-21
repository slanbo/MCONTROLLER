#include "Control.hpp"
#include "TuneObjectsExt.hpp"
#include <string>
#include "GUI.h"
#include "Lcd_Driver.h"
#include "SocketObjectsExt.hpp"
#include "Sensors.hpp"
#include "ScreenObjectsExt.hpp"

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
	_fillVector(SocketsVector, BaseUnitSocketsV, SocketsTune);
}

SocketsControl::SocketsControl(std::string name, 
	intTune* onOffTune, 
	IntVectorTune* socketsTune)
	: ControlBase(id, name, onOffTune)
	, SocketsTune()

{
	_fillVector(SocketsVector, BaseUnitSocketsV, SocketsTune);

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
	createTimeProfileFnc ctpFnc
	)
	: ControlBase(id, name, onOffTune)
	, SensorsTune(sensorsTune)
	, UpSocketsTune(upSocketsTune)
	, DownSocketsTune(downSocketsTune)
{
	ctpFnc(tProfile, timeProfileTune);
	_fillVector(UpSocketsVector, BaseUnitSocketsV, UpSocketsTune);
	_fillVector(DownSocketsVector, BaseUnitSocketsV, DownSocketsTune);
	_fillVector(SensorsVector, ADCSensorsV, SensorsTune);
}

SensorsSocketsControl::SensorsSocketsControl(
	std::string name,
	intTune* onOffTune,
	IntVectorTune* sensorsTune,
	IntVectorTune* upSocketsTune,
	IntVectorTune* downSocketsTune,
	intTune* timeProfileTune,
	createTimeProfileFnc ctpFnc)
	: ControlBase(name, onOffTune)
	, SensorsTune(sensorsTune)
	, UpSocketsTune(upSocketsTune)
	, DownSocketsTune(downSocketsTune)
{
	ctpFnc(tProfile, timeProfileTune);
	_fillVector(UpSocketsVector, BaseUnitSocketsV, UpSocketsTune);
	_fillVector(DownSocketsVector, BaseUnitSocketsV, DownSocketsTune);
	_fillVector(SensorsVector, ADCSensorsV, SensorsTune);
}

void SensorsSocketsControl::ExecuteStep()
{
	
	uint16_t aim_t = tProfile->getVal();
	uint16_t sumT = 0;
	for (auto term : SensorsVector)
	{
		term->getTemperature();
		sumT += term->temp; 
	}
	uint16_t current_t = sumT / SensorsVector.size();
	
	if (isActive())
	{
		if (current_t < aim_t - 2) 
		{
			SwitchSockets(DownSocketsVector, 0xffff);
			return;
		}
		if (current_t < aim_t - 1)
		{
			SwitchSockets(DownSocketsVector, 2000);
			return;
		}
		if (current_t < aim_t)
		{
			SwitchSockets(DownSocketsVector, 1000);
			return;
		}if (current_t >= aim_t)
		{
			SwitchSockets(DownSocketsVector, 0);
			return;
		}
	}
	else
	{
		SwitchSockets(DownSocketsVector, 0);
		return;
	}

}

void SensorsSocketsControl::FillScreen()
{
	Info_SubHeader.SetText(Name, false);
	Info_FirstString.Set_Prefix_IntVal_Postfix_Text("Текущ.: ", _get_current_val(), 3, CO, true);
	Info_SecondString.Set_Prefix_IntVal_Postfix_Text("Целев.: ", _get_aim_val(), 3, CO, true);
	Info_ThirdString.Set_Prefix_IntVal_Postfix_Text("Нагр.(ВТ): ", 10, 4, "", true);
	Info_FourthString.SetText("", false);
	
}


void SensorsSocketsControl::_fillVector(std::vector<BaseObject*> &vectorOut, std::vector<BaseObject*> &vectorIn, IntVectorTune* tune)
{
	
	vectorOut.clear();
	for (auto inItem : vectorIn)
		for (auto tuneval : tune->_getVal())
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

void SensorsSocketsControl::SwitchSockets(uint16_t powerVT)
{
}



