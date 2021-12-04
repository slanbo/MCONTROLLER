#pragma once
#include "ADCDev.hpp"
#include <vector>

ADCDev* ADCD_RANGE1 = new ADCDev(1, "RANGE1");
ADCDev* ADCD_RANGE2 = new ADCDev(2, "RANGE2");
ADCDev* ADCD_RANGE3 = new ADCDev(3, "RANGE3");
ADCDev* ADCD_RANGE4 = new ADCDev(4, "RANGE4");

std::vector<ADCDev*> ADCDevises = { ADCD_RANGE1, ADCD_RANGE2, ADCD_RANGE3, ADCD_RANGE4 };

