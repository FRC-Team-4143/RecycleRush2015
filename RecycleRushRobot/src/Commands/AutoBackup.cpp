#include "AutoBackup.h"
#include "Drive.h"
#include "Sleep.h"
AutoBackup::AutoBackup() {
	// TODO - Use AddSequential and AddParallel here
	AddSequential (new Sleep(SmartDashboard::GetNumber("AutoSleep", 3)));
	AddSequential (new Drive (-0.3, 0, 0, true, 1.2));
}
