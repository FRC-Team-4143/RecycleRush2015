#include "SwitchMode.h"
#include "Robot.h"

SwitchMode::SwitchMode()
{
	//Requires(Robot::completeElevator);
}

// Called just before this Command runs the first time
void SwitchMode::Initialize()
{
	Robot::completeElevator->SetMode();
}

// Called repeatedly when this Command is scheduled to run
void SwitchMode::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool SwitchMode::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void SwitchMode::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SwitchMode::Interrupted()
{

}
