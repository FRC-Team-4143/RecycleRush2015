#include "CompleteLower.h"
#include "Robot.h"

CompleteLower::CompleteLower()
{
	Requires(Robot::completeElevator);
}

// Called just before this Command runs the first time
void CompleteLower::Initialize()
{
	Robot::completeElevator->CompleteLower();
}

// Called repeatedly when this Command is scheduled to run
void CompleteLower::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool CompleteLower::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void CompleteLower::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CompleteLower::Interrupted()
{

}
