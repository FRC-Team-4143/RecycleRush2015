#include "AutoBinMove.h"
#include "BinUpTimed.h"
#include "Drive.h"
#include "RotateBy.h"
#include "Sleep.h"
#include "BinDownTimed.h"
AutoBinMove::AutoBinMove() {
	// TODO - Use AddSequential and AddParallel here
	AddSequential (new Sleep(SmartDashboard::GetNumber("AutoDelay")));
	AddSequential (new BinUpTimed (SmartDashboard::GetNumber("AutoBinUpTime")));
	AddSequential (new Drive (-0.5, 0, 0, true, (SmartDashboard::GetNumber("AutoDriveTime"))));
	AddSequential (new RotateBy ("RotateBy90", (SmartDashboard::GetNumber("AutoRotateDirection"))));
	AddSequential (new BinDownTimed (SmartDashboard::GetNumber("AutoBinDownTime")));
	AddSequential (new Drive (-0.5, 0, 0, true, (SmartDashboard::GetNumber("AutoFinalBackup"))));

}
