#include "CycleLightMode.h"
#include "Robot.h"

CycleLightMode::CycleLightMode()
{
	SetRunWhenDisabled(true);
}

// Called just before this Command runs the first time
void CycleLightMode::Initialize()
{
	Robot::completeElevator->CycleLightMode();
}

// Called repeatedly when this Command is scheduled to run
void CycleLightMode::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool CycleLightMode::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void CycleLightMode::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CycleLightMode::Interrupted()
{

}
