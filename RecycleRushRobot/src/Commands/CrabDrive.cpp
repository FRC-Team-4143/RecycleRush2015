#include "CrabDrive.h"
#include <math.h>

CrabDrive::CrabDrive() {
	Requires(Robot::driveTrain);
}

// Called just before this Command runs the first time
void CrabDrive::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void CrabDrive::Execute() {
	Robot::driveTrain->Crab(
		Robot::oi->GetJoystickZ(),
		-Robot::oi->GetJoystickY(),
		Robot::oi->GetJoystickX()
	);
}

// Make this return true when this Command no longer needs to run execute()
bool CrabDrive::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CrabDrive::End() {
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CrabDrive::Interrupted() {
	End();
}
