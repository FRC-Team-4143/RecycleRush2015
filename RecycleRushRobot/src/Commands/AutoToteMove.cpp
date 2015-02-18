#include <Commands/AutoToteMove.h>
#include "Tote3UpTimed.h"
#include "Drive.h"
#include "RotateBy.h"
#include "Sleep.h"
#include "Tote3DownTimed.h"
AutoToteMove::AutoToteMove() {
	// TODO - Use AddSequential and AddParallel here
	AddSequential (new Sleep(SmartDashboard::GetNumber("AutoSleep", 1)));
	AddSequential (new Tote3UpTimed (5));
	AddSequential (new Drive (-0.5, 0, 0, true, 3));
	AddSequential (new RotateBy ("RotateBy90", 90));
	AddSequential (new Drive (0.3, 0, 0, true, 1.5));
	AddSequential (new Tote3DownTimed (5));
}
