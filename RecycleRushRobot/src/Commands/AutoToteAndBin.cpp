#include "AutoToteAndBin.h"
#include "BinUpTimed.h"
#include "BinDownTimed.h"
#include "Drive.h"
#include "RotateBy.h"
#include "Sleep.h"
//#include "Tote3UpTimed.h"
//#include "Tote3DownTimed.h"
AutoToteAndBin::AutoToteAndBin() {
	// TODO - Use AddSequential and AddParallel here
	AddSequential (new Sleep(SmartDashboard::GetNumber("AutoSleep", 0.5)));
	//AddSequential (new Tote3UpTimed (4));   //uncomment if using a different elevator
	AddSequential (new BinUpTimed (4));
	AddSequential (new Drive (-0.4, 0, 0, true, 6));
	AddSequential (new RotateBy ("RotateBy90", 90));
	//AddSequential (new Tote3DownTimed (4));    //uncomment if using a different elevator
	AddSequential (new BinDownTimed (4));
	AddSequential (new Drive (-0.5, 0, 0, true, 1));
}
