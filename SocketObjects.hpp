#include "Socket.hpp"
#include "TuneObjectsExt.hpp"

plugSocket* upSocket = new plugSocket(1, "UP Socket", SSD1_GPIO_Port, SSD1_Pin, upSocketLoadPower);
plugSocket* midSocket = new plugSocket(4, "MID Socket", SSD2_GPIO_Port, SSD2_Pin, midSocketLoadPower);
plugSocket* downSocket = new plugSocket(2, "DOWN Socket", SSD3_GPIO_Port, SSD3_Pin, downSocketLoadPower);
plugSocket* V12_Socket = new plugSocket(3, "12V Socket", SSD2_GPIO_Port, SSD2_Pin, v12LoadPower);

std::vector<plugSocket *> BaseUnitSocketsV = { upSocket, downSocket, V12_Socket, midSocket };

