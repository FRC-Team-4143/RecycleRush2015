#include "RunCamera.h"
#include "../Robot.h"

RunCamera::RunCamera(int cameraNumber)
{
	SetRunWhenDisabled(true);
	cameraNum = cameraNumber;
}

// Called just before this Command runs the first time
void RunCamera::Initialize()
{
	//Robot::camera->StartCamera(cameraNum);
}

// Called repeatedly when this Command is scheduled to run
void RunCamera::Execute()
{
	//Robot::camera->ShowCamera(cameraNum);
}

// Make this return true when this Command no longer needs to run execute()
bool RunCamera::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void RunCamera::End()
{
	//Robot::camera->StopCamera(cameraNum);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RunCamera::Interrupted()
{
	//Robot::camera->StopCamera(cameraNum);
}
