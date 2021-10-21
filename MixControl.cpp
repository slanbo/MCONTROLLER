#include "MixControl.hpp"
#include <cassert>
#include "TuneObjectsExt.hpp"
#include "ControlObjectsExt.hpp"
#include "ScreenObjectsExt.hpp"

MixControl::MixControl(std::string name,
	intTune* onOffTune,
	std::vector<plugSocket*> &sockets,
	intTune * modeTune,
	std::vector<plugSocket*> &heatingSockets)
	: SocketsControl(name,
	onOffTune,
	sockets
	)
	, ModeTune(modeTune)
	, HeatingSockets(heatingSockets)
{
}


void MixControl::FillScreen()
{
	Info_SubHeader.SetText(Name, false);
	
	char statestr[MAX_CHARS_IN_SCREEN * 2] = "Cост:";
	if(getState())
		strcat(statestr, " ВКЛ") ;
	else
		strcat(statestr, " ВЫКЛ");
	
	Info_FirstString.SetText(statestr, true);
	Info_SecondString.SetText("Режим работы:", true);
	
	char modestr[MAX_CHARS_IN_SCREEN * 2] = { 0 };
	switch (ModeTune->val)
	{
	case 0:	//always on
		{
			strcpy(modestr, "ВСЕГДА ВКЛ.");
			break;
		}	
	case 1:	//switch on if heating
		{
			strcpy(modestr, "ВКЛ ЕСЛИ НАГР.");
			break;
		}
	case 2:	//switch on if not heating
		{
			strcpy(modestr, "ВКЛ ЕСЛИ НЕ НАГР.");
			break;
		}
		case 3:	//pauses
		{
			strcpy(modestr, "ВКЛ ПАУЗАМИ");
			break;
		}
	default: //allways off
		{
			strcpy(modestr, "НЕОПРЕД.");
			break;
		}
	}
	
	Info_ThirdString.SetText(modestr, true);
	Info_FourthString.SetText("", false);
	
	getRectCoordinates(Info_Screen, Left_X, Top_Y, Right_X, Bottom_Y);

}

void MixControl::ExecuteStep()
{
	assert(ModeTune->val < 3);
	
	if (isActive())
	{
		switch (ModeTune->val)
		{
		case 0:	//always on
			{
				for (auto sock : Sockets)
					SwitchSockets(9999);
				break;
			}	
		case 1:	//switch on if heating
			{
				bool isHeating = false;
				for (auto heatingsock : HeatingSockets)
					if(heatingsock->getSocketState())
						isHeating = true;
				if (isHeating)
					SwitchSockets(9999);
				else
					SwitchSockets(0);
				break;
			}
		case 2:	//switch on if not heating
			{
				bool isHeating;
				for (auto heatingsock : HeatingSockets)
					if (heatingsock->getSocketState())
						isHeating = true;
				if (isHeating)
					SwitchSockets(0);
				else
					SwitchSockets(9999);
				break;
			}	
		case 3:	//pauses
			{
				bool SwitchedOn = getState();
			
				if (SwitchedOn)
				{
					stepsSwitchedOff = 0;
					stepsSwitchedOn += 1;
					if (stepsSwitchedOn >= SwitchedOnPumpTime.val)
					{
						SwitchSockets(0);
					}
				}
				else
				{
					stepsSwitchedOn = 0;
					stepsSwitchedOff += 1;
					if (stepsSwitchedOff >= SwitchedOffPumpTime.val)
					{
						SwitchSockets(9999);
					}

				}
				break;
			}
		default: //allways off
			{
				SwitchSockets(0);
				break;
			}
		}
	}	
	else
	{
		SwitchSockets(0);
	}
	return;		
}

bool MixControl::getState()
{
	bool SwitchedOn = false;
			
	for (auto sock : Sockets)
		if (sock->getSocketState())
			SwitchedOn = true;
	
	return SwitchedOn;
}

bool MixControl::isActive()
{
	bool active = false;
	
	if(isOn())
		active = true;
	
	if (delayBeginControl.isOn()) 
		{
			if (delayBeginControl.isActive())
				active = true;
			else
				active = false;
		}
	
	if (delayEndControl.isOn())
	{
		if (delayEndControl.isActive())
			active = false;
		else
			active = true;
	}
	
	return active;
}




