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
	AddSequential (new Sleep(SmartDashboard::GetNumber("AutoDelay")));
	//AddSequential (new Tote3UpTimed (SmartDashboard::GetNumber("AutoTote3UpTimed")));   //uncomment if using a different elevator
	AddSequential (new BinUpTimed (SmartDashboard::GetNumber("AutoBinUpTime")));
	AddSequential (new Drive (-0.75, 0, 0, true, (SmartDashboard::GetNumber("AutoDriveTime"))));	//AddSequential (new RotateBy ("RotateBy90", (SmartDashboard::GetNumber("AutoRotateDirection"))));
	//AddSequential (new Tote3DownTimed (SmartDashboard::GetNumber("AutoTote3DownTimed")));    //uncomment if using a different elevator
	AddSequential (new BinDownTimed (SmartDashboard::GetNumber("AutoBinDownTime")));
	AddSequential (new Drive (-0.75, 0, 0, true, (SmartDashboard::GetNumber("AutoFinalBackup"))));
}
