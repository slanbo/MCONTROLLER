#ifndef __SOCKETS__H
#define __SOCKETS__H

#include "Socket.hpp"
	
#define DEV_SOCKETS_SIZE 3
	
	extern plugSocket upSocket;
	extern plugSocket downSocket;
	extern plugSocket V12_Socket;

	extern std::vector <plugSocket*> BaseUnitSocketsV;


	bool SwitchPowerSockets(uint16_t powerVT, plugSocket** sockets, uint8_t size);
	uint16_t GetSwitchedOnLoadPower(plugSocket** sockets, uint8_t size);
	

#endif	