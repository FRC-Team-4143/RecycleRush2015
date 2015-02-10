#include "BinDown.h"
#include "../RobotMap.h"

BinDown::BinDown()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void BinDown::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void BinDown::Execute()
{
	RobotMap::binElevatorMotor->Set(-1);
}

// Make this return true when this Command no longer needs to run execute()
bool BinDown::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void BinDown::End()
{
	RobotMap::binElevatorMotor->Set(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void BinDown::Interrupted()
{
	RobotMap::binElevatorMotor->Set(0);
}
