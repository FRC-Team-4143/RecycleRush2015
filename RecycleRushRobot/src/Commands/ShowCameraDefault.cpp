#include "ShowCameraDefault.h"
#include "../Robot.h"

ShowCameraDefault::ShowCameraDefault()
{
	Requires(Robot::camera);
}

// Called just before this Command runs the first time
void ShowCameraDefault::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void ShowCameraDefault::Execute()
{
	Robot::camera->ShowCamera(Robot::camera->cameraCurrent);
}

// Make this return true when this Command no longer needs to run execute()
bool ShowCameraDefault::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void ShowCameraDefault::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShowCameraDefault::Interrupted()
{

}
