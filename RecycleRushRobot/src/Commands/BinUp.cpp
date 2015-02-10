#include "BinUp.h"
#include "../RobotMap.h"

BinUp::BinUp()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void BinUp::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void BinUp::Execute()
{
	RobotMap::binElevatorMotor->Set(1);
}

// Make this return true when this Command no longer needs to run execute()
bool BinUp::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void BinUp::End()
{
	RobotMap::binElevatorMotor->Set(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void BinUp::Interrupted()
{
	RobotMap::binElevatorMotor->Set(0);
}
