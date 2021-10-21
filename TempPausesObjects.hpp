#include "TempPauses.hpp"

TempPause MashPause_1(1, mashTermistorsV, mashingSocketsV);
TempPause MashPause_2(2, mashTermistorsV, mashingSocketsV);
TempPause MashPause_3(3, mashTermistorsV, mashingSocketsV);
TempPause MashPause_4(4, mashTermistorsV, mashingSocketsV);
TempPause MashPause_5(5, mashTermistorsV, mashingSocketsV);
TempPause MashPause_6(6, mashTermistorsV, mashingSocketsV);

std::vector <TempPause*> MashingPausesV = {
	&MashPause_1,
	&MashPause_2,
	&MashPause_3,
	&MashPause_4,
	&MashPause_5,
	&MashPause_6
};

TempPause BoilPause_1(1, boilTermistorsV, boilingSocketsV);
TempPause BoilPause_2(2, boilTermistorsV, boilingSocketsV);
TempPause BoilPause_3(3, boilTermistorsV, boilingSocketsV);

std::vector < TempPause*> BoilingPausesV = {
	&MashPause_1,
	&MashPause_2,
	&MashPause_3
	
};
