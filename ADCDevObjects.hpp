#pragma once
#include "ADCDev.hpp"
#include <vector>

ADCDev ADCD_RANGE1(1, "RANGE1");
ADCDev ADCD_RANGE2(2, "RANGE1");
ADCDev ADCD_RANGE3(3, "RANGE1");
ADCDev ADCD_RANGE4(4, "RANGE1");

std::vector<ADCDev*> ADCDevises = { &ADCD_RANGE1, &ADCD_RANGE2, &ADCD_RANGE3, &ADCD_RANGE4 };

