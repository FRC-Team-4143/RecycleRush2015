#include "WaitForRelease.h"
#include "Robot.h"

WaitForRelease::WaitForRelease()
{

}

// Called just before this Command runs the first time
void WaitForRelease::Initialize()
{
}

// Called repeatedly when this Command is scheduled to run
void WaitForRelease::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool WaitForRelease::IsFinished()
{
	return Robot::oi->GetBackButton();
}

// Called once after isFinished returns true
void WaitForRelease::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void WaitForRelease::Interrupted()
{

}
