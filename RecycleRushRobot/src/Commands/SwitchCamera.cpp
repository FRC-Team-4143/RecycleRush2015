#include "SwitchCamera.h"
#include "../Robot.h"

SwitchCamera::SwitchCamera()
{
	//Requires(Robot::camera);
	SetRunWhenDisabled(true);
}

// Called just before this Command runs the first time
void SwitchCamera::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void SwitchCamera::Execute()
{
	//Robot::camera->SwitchCamera();
}

// Make this return true when this Command no longer needs to run execute()
bool SwitchCamera::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void SwitchCamera::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SwitchCamera::Interrupted()
{

}
