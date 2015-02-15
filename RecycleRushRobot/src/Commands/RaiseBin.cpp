#include "RaiseBin.h"
#include "../RobotMap.h"


RaiseBin::RaiseBin(double distance)
{
	dist = distance;
}

// Called just before this Command runs the first time
void RaiseBin::Initialize()
{
	current = RobotMap::toteElevator4PID->GetSetpoint();
}

// Called repeatedly when this Command is scheduled to run
void RaiseBin::Execute()
{
	RobotMap::toteElevator4PID->SetSetpoint(current + dist);
}

// Make this return true when this Command no longer needs to run execute()
bool RaiseBin::IsFinished()
{
	return RobotMap::toteElevator4PID->OnTarget();
}

// Called once after isFinished returns true
void RaiseBin::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RaiseBin::Interrupted()
{

}
