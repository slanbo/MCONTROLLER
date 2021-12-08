#include "TuneObjectsExt.hpp"
#include "DateControl.hpp"
#include "MotionControl.hpp"
#include "MixControl.hpp"
#include "TimeProfiles.hpp"
#include <vector>
#include "Control.hpp"
#include "PCounterControl.hpp"

SensorsSocketsControl* first_SensorsSocketsControl = new SensorsSocketsControl();
SensorsSocketsControl* second_SensorsSocketsControl = new SensorsSocketsControl();
SensorsSocketsControl* third_SensorsSocketsControl = new SensorsSocketsControl();
SensorsSocketsControl* forth_SensorsSocketsControl = new SensorsSocketsControl();

std::vector<SensorsSocketsControl*> controlsVector;
