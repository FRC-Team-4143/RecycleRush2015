#include "LowerBin.h"
#include "../RobotMap.h"

LowerBin::LowerBin(double distance)
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	dist = distance;
}

// Called just before this Command runs the first time
void LowerBin::Initialize()
{
	current = RobotMap::toteElevator4PID->GetSetpoint();
}

// Called repeatedly when this Command is scheduled to run
void LowerBin::Execute()
{
	RobotMap::toteElevator4PID->SetSetpoint(current - dist);
}

// Make this return true when this Command no longer needs to run execute()
bool LowerBin::IsFinished()
{
	return RobotMap::toteElevator4PID->OnTarget();
}

// Called once after isFinished returns true
void LowerBin::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LowerBin::Interrupted()
{

}
