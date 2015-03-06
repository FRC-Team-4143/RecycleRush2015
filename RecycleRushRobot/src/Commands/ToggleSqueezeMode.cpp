#include "ToggleSqueezeMode.h"
#include "Robot.h"

ToggleSqueezeMode::ToggleSqueezeMode()
{
	Requires(Robot::completeElevator);
}

// Called just before this Command runs the first time
void ToggleSqueezeMode::Initialize()
{
	Robot::completeElevator->ToggleSqueezeMode();
}

// Called repeatedly when this Command is scheduled to run
void ToggleSqueezeMode::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool ToggleSqueezeMode::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void ToggleSqueezeMode::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ToggleSqueezeMode::Interrupted()
{

}
