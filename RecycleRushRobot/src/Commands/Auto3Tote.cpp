#include <Commands/Auto3Tote.h>
#include "Tote3UpTimed.h"
#include "Drive.h"
#include "RotateBy.h"
#include "Sleep.h"
#include "Tote3DownTimed.h"
Auto3Tote::Auto3Tote() {
	// TODO - Use AddSequential and AddParallel here
	//AddSequential (new Sleep(SmartDashboard::GetNumber("AutoDelay")));  /////no delay we're going to need the time
	AddSequential (new Tote3UpTimed (SmartDashboard::GetNumber("AutoToteUpTime")));
	AddSequential (new Drive (-0.75, 0, 0, true, 1.5)); //encoders/use of vision here instead of time preferably
	AddParallel (new Tote3UpTimed (SmartDashboard::GetNumber("AutoToteUpTime")));
	AddParallel (new Drive (0, 0.75, 0, true, 2));
	AddSequential (new Drive (0.75, 0, 0, true, 1.5));
	AddSequential (new Tote3UpTimed (SmartDashboard::GetNumber("AutoToteUpTime")));
	AddSequential (new Drive (-0.75, 0, 0, true, 1.5));
	AddParallel (new Drive (0, 0.75, 0, true, 2));
	AddParallel (new Tote3UpTimed (SmartDashboard::GetNumber("AutoToteUpTime")));
	AddSequential (new Drive (0.75, 0, 0, true, 1.5));
	AddSequential (new Tote3UpTimed (SmartDashboard::GetNumber("AutoToteUpTime")));
	AddParallel (new Drive (-0.75, 0, 0, true, 2));
	AddParallel (new Tote3UpTimed (SmartDashboard::GetNumber("AutoToteUpTime")));
	AddSequential (new Tote3DownTimed (SmartDashboard::GetNumber("AutoToteDownTime")));
	AddSequential (new Drive (-0.75, 0, 0, true, (SmartDashboard::GetNumber("AutoFinalBackup"))));
	AddSequential (new RotateBy ("RotateBy90", (SmartDashboard::GetNumber("AutoRotateDirection"))));
}
