#include "AutonomousCommand.h"
#include "Tote3UpTimed.h"
#include "Drive.h"
#include "RotateBy.h"
#include "Sleep.h"
AutonomousCommand::AutonomousCommand() {
	// TODO - Use AddSequential and AddParallel here
	AddSequential (new Sleep(SmartDashboard::GetNumber("AutoSleep", 3)));
	AddSequential (new Tote3UpTimed (3));
	AddSequential (new Drive (-0.5, 0, 0, true, 3));
	AddSequential (new RotateBy ("RotateBy90", 90));
	AddSequential (new Drive (0.3, 0, 0, true, 1.5));
}
