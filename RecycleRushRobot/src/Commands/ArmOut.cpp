#include "ArmOut.h"
#include "../RobotMap.h"

ArmOut::ArmOut()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void ArmOut::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void ArmOut::Execute()
{

	if (RobotMap::binArmPos >= 0){
		RobotMap::binArmMotor->Set(0.5);
	} else {
		RobotMap::binArmMotor->Set(0);
	}

}

// Make this return true when this Command no longer needs to run execute()
bool ArmOut::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void ArmOut::End()
{
	RobotMap::binArmMotor->Set(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ArmOut::Interrupted()
{
	RobotMap::binArmMotor->Set(0);
}
