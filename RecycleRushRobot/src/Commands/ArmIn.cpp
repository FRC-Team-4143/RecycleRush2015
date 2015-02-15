#include "ArmIn.h"
#include "../RobotMap.h"

ArmIn::ArmIn()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void ArmIn::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void ArmIn::Execute()
{

	if (RobotMap::binArmPos->GetDistance() <= 30*30){//inches * counts per inch
		RobotMap::binArmMotor->Set(-0.5);
	} else {
		RobotMap::binArmMotor->Set(0);
	}

}

// Make this return true when this Command no longer needs to run execute()
bool ArmIn::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void ArmIn::End()
{
	RobotMap::binArmMotor->Set(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ArmIn::Interrupted()
{
	RobotMap::binArmMotor->Set(0);
}
