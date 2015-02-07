#include "LowerElevator.h"
#include "../Robot.h"

LowerElevator::LowerElevator()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void LowerElevator::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void LowerElevator::Execute()
{
	Robot::toteElevator1->GoDown();
}

// Make this return true when this Command no longer needs to run execute()
bool LowerElevator::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void LowerElevator::End()
{
	Robot::toteElevator1->HoldPosition();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LowerElevator::Interrupted()
{
	Robot::toteElevator1->HoldPosition();
}
