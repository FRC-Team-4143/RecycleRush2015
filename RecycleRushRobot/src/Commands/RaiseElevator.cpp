#include "RaiseElevator.h"
#include "../Robot.h"

RaiseElevator::RaiseElevator()
{
	Requires(Robot::toteElevator1);
}

// Called just before this Command runs the first time
void RaiseElevator::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void RaiseElevator::Execute()
{
	Robot::toteElevator1->GoUp();
}

// Make this return true when this Command no longer needs to run execute()
bool RaiseElevator::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void RaiseElevator::End()
{
	Robot::toteElevator1->HoldPosition();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RaiseElevator::Interrupted()
{
	Robot::toteElevator1->HoldPosition();
}
