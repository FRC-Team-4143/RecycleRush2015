#include <Commands/AutoToteMove.h>
#include "Tote3UpTimed.h"
#include "Drive.h"
#include "RotateBy.h"
#include "Sleep.h"
#include "Tote3DownTimed.h"
AutoToteMove::AutoToteMove() {
	// TODO - Use AddSequential and AddParallel here
	AddSequential (new Sleep(SmartDashboard::GetNumber("AutoDelay")));
	AddSequential (new Tote3UpTimed (SmartDashboard::GetNumber("AutoToteUpTime")));
	AddSequential (new Drive (-0.5, 0, 0, true, (SmartDashboard::GetNumber("AutoDriveTime"))));
	AddSequential (new RotateBy ("RotateBy90", (SmartDashboard::GetNumber("AutoRotateDirection"))));
	AddSequential (new Tote3DownTimed (SmartDashboard::GetNumber("AutoToteDownTime")));
	AddSequential (new Drive (-0.5, 0, 0, true, (SmartDashboard::GetNumber("AutoFinalBackup"))));
}
