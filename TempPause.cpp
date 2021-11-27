#include "TempPause.hpp"
#include "ScreenObjectsExt.hpp"

PauseState TempPause::GetState()
{
	if (TempTime->Time == 0 | TempTime->Temperature == 0)
	{
		return INACTIVE;
	}
	else
	{	
		if (TempTime->Time >= Steps_StayOn * EXECUTE_STEP_PERIOD_SEC)
		{
			return COMPLETED;
		}
		else
		{
			if (TempTime->Temperature < getCurrentTemp() - 1)
			{
				return HEATING_MAX;
			}
			if (TempTime->Temperature >= getCurrentTemp() - 1 & TempTime->Temperature < getCurrentTemp())
			{
				return HEATING_MIN;
			}
			if (TempTime->Temperature >= getCurrentTemp() & TempTime->Temperature < getCurrentTemp() + 1)
			{
				return STAY_ON;
			}
			if (TempTime->Temperature >= getCurrentTemp() + 1)
			{
				return COOLING;
			}
		}
	}
	return UNKNOWN;
}

bool TempPause::ExecuteStep()
{
	
	active = false;
	
	PauseState state = GetState();
	
	if (state != COMPLETED & state != INACTIVE)
	{
		active = true;
	}
	
	if (state == HEATING_MAX)
	{
		Steps_Heating += 1;
	}
	if (state == HEATING_MIN)
	{
		Steps_Heating += 1;
	}
	if (state == STAY_ON)
	{
		Steps_StayOn += 1;
	}
	if (state == COOLING)
	{
		Steps_Cooling += 1;
	}	
	
	SwitchSockets();
	return active;
	
}


void TempPause::FillScreen()
{
	char prefixStr[40];
	char header[40] = "ПАУЗА ";
	strcat(header, Name);
	Info_SubHeader->SetText(header, false);
	
	PauseState currState = GetState();
	switch (currState)
	{
	case INACTIVE:
		{
			strcpy(prefixStr, "Сост.: НЕАКТ.");
			break;
		}
	case HEATING_MAX:
		{
			strcpy(prefixStr, "Сост.: MAX НАГР.");
			break;
		}
	case HEATING_MIN:
		{
			strcpy(prefixStr, "Сост.: MIN НАГР.");
			break;
		}
	case STAY_ON:
		{
			strcpy(prefixStr, "Сост.: ПАУЗА.");
			break;
		}
	case COOLING:
		{
			strcpy(prefixStr, "Сост.: ОХЛАЖД.");
			break;
		}
	case COMPLETED:
		{
			strcpy(prefixStr, "Сост.: ВЫПОЛН.");
			break;
		}
	default:
		{
			strcpy(prefixStr, "Сост.: НЕОПР.");
			break;
		}
	}
	Info_FirstString->SetText(prefixStr, true);
	
	uint16_t stay_on_min = (uint16_t)(Steps_StayOn * EXECUTE_STEP_PERIOD_SEC) / 60;
	Info_SecondString->Set_Prefix_IntVal_Postfix_Text("Выполнено: ", stay_on_min, 3, "",true);
	
	uint16_t temp = getCurrentTemp();
	Info_ThirdString->Set_Prefix_IntVal_Postfix_Text("Тек. t: ", temp, 3, CO, true);
}



void TempPause::RestoreTunes()
{
	TempTune->restore();
	TempTime->Temperature = TempTune->_getVal();
	
	TimeTune->restore();
	TempTime->Time = TimeTune->_getVal();
	
	Time_StayOn_Tune->restore();
	Steps_StayOn = (uint16_t)Time_StayOn_Tune->_getVal() / EXECUTE_STEP_PERIOD_SEC;

}

void TempPause::SwitchSockets()
{
	
	PauseState state = GetState();
	if (state == HEATING_MAX)
	{
		for (uint8_t i = 0; i < 2; i++)
		{
			//HeaterSockets[i]->SwitchOn();
		}
	}
	if (state == HEATING_MIN)
	{
		plugSocket* minSocket;
		uint16_t minLoadPower = 0xffff;
		
		for (uint8_t i = 0; i < 2; i++)
		{
			//if (HeaterSockets[i]->getLoadpowerVT() < minLoadPower & HeaterSockets[i]->getLoadpowerVT() > 0) 
			//{
			//	minSocket = HeaterSockets[i];
			//	minLoadPower = HeaterSockets[i]->getLoadpowerVT();
			//}
		}
		for (uint8_t i = 0; i < 2; i++)
		{
			//if (HeaterSockets[i] == minSocket)
			//{
			//	HeaterSockets[i]->SwitchOn();
			//}
			//else
			//{
			//	HeaterSockets[i]->SwitchOff();
			//}
		}
	}
	if (state != HEATING_MAX | state != HEATING_MIN) 
	{
		for (uint8_t i = 0; i < 2; i++)
		{
			//HeaterSockets[i]->SwitchOff();
		}
	}
}

void TempPause::init(std::vector<NTC_10K_B3950*> &termistors,
	std::vector<plugSocket*> &heaterSockets)
{
	//Termistors = termistors;
	//HeaterSockets = heaterSockets;
}

void TempPause::initTempTime(TempPauseTemplate* tempTime)
{
	TempTime = tempTime;
	Steps_StayOn = 0;
	Steps_Heating = 0;
	Steps_Cooling = 0;
	active = false;
	Time_StayOn_Tune->_setVal(0);
	Time_StayOn_Tune->save();
}


TempPause::TempPause
	(
	uint8_t index,
	IntVectorTune* sensorsTune,
	IntVectorTune* socketsTune
	):
	Index(index)
{
	
}
;

uint16_t TempPause::getCurrentTemp()
{
	return 0;
}
;

TempPauseTemplate::TempPauseTemplate(uint16_t temperature, 
	uint16_t time)
	: Time(time)
	, Temperature(temperature)
{
	
}
;

