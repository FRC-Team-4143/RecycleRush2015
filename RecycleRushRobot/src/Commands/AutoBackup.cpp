#include "AutoBackup.h"
#include "Drive.h"
#include "Sleep.h"
#include "RotateBy.h"
AutoBackup::AutoBackup() {
	// TODO - Use AddSequential and AddParallel here
	AddSequential (new Sleep(SmartDashboard::GetNumber("AutoSleep", 1)));
	AddSequential (new Drive (-0.5, 0, 0, true, 4));
	AddSequential (new RotateBy ("RotateBy90", 90));
}
