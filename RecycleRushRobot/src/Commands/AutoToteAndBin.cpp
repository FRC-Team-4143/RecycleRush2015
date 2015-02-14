#include "AutoToteAndBin.h"
#include "BinUpTimed.h"
#include "Drive.h"
#include "RotateBy.h"
#include "Sleep.h"
#include "Tote3UpTimed.h"
AutoToteAndBin::AutoToteAndBin() {
	// TODO - Use AddSequential and AddParallel here
	AddSequential (new Sleep(SmartDashboard::GetNumber("AutoSleep", 3)));
	AddSequential (new Tote3UpTimed (6));
	AddSequential (new Drive (-0.5, 0, 0, true, 3));
	AddSequential (new RotateBy ("RotateBy90", 90));
}
