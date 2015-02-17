#include "AutoBinMove.h"
#include "BinUpTimed.h"
#include "Drive.h"
#include "RotateBy.h"
#include "Sleep.h"
#include "BinDownTimed.h"
AutoBinMove::AutoBinMove() {
	// TODO - Use AddSequential and AddParallel here
	AddSequential (new Sleep(SmartDashboard::GetNumber("AutoSleep", 1.5)));
	AddSequential (new BinUpTimed (2));
	AddSequential (new Drive (-0.5, 0, 0, true, 4.5));
	AddSequential (new RotateBy ("RotateBy90", 120));
	AddSequential (new BinDownTimed (2.5));
	AddSequential (new Drive (-0.5, 0, 0, true, 1));

}
