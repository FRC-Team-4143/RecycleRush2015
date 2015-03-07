#include "AutoBackup.h"
#include "Drive.h"
#include "Sleep.h"
#include "RotateBy.h"
AutoBackup::AutoBackup() {
	// TODO - Use AddSequential and AddParallel here
	AddSequential (new Sleep(SmartDashboard::GetNumber("AutoSleep")));
	AddSequential (new Drive (-0.75, 0, 0, true, (SmartDashboard::GetNumber("TimedDrive"))));
	AddSequential (new RotateBy ("RotateBy90", (SmartDashboard::GetNumber("RotateBy"))));
}
