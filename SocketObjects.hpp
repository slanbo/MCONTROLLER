#include "Socket.hpp"

plugSocket* upSocket = new plugSocket(0, "UP Socket", SSD1_GPIO_Port, SSD1_Pin, upSocketLoadPower);
plugSocket* downSocket = new plugSocket(1, "DOWN Socket", SSD3_GPIO_Port, SSD3_Pin, downSocketLoadPower);
plugSocket* V12_Socket = new plugSocket(2, "12V Socket", SSD2_GPIO_Port, SSD2_Pin, v12LoadPower);

std::vector<plugSocket *> BaseUnitSocketsV = { upSocket, downSocket, V12_Socket };

