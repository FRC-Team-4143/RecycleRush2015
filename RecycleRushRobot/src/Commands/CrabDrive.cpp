#include "CrabDrive.h"
#include "../Robot.h"

CrabDrive::CrabDrive() : Command("Crab Drive") {
	std::cout << "CrabDrive::CrabDrive" << std::endl;

	Requires(Robot::driveTrain);
}

// Called just before this Command runs the first time
void CrabDrive::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void CrabDrive::Execute() {
	float x = Robot::oi->GetJoystickX();
	float y = Robot::oi->GetJoystickY();
	float z = Robot::oi->GetJoystickZ();
	//std::cout << "X " << x << ", Y " << y << ", Z " << z << std::endl;
	Robot::driveTrain->Crab(z, -y, x, true);
	//Robot::driveTrain->GyroCrab(0, -y, x, true);
	//Robot::driveTrain->FieldCentricCrab(z,-y,x, true);
}

// Make this return true when this Command no longer needs to run Execute.
bool CrabDrive::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CrabDrive::End() {
}

// Called when another command which requires this subsystem is scheduled to run
void CrabDrive::Interrupted() {
	End();
}
