#include "PrepareElevators.h"
#include "RobotMap.h"

PrepareElevators::PrepareElevators()
{

}

// Called just before this Command runs the first time
void PrepareElevators::Initialize()
{
	elevator1 = RobotMap::toteElevator1PID;
	elevator2 = RobotMap::toteElevator2PID;
	elevator3 = RobotMap::toteElevator3PID;
}

// Called repeatedly when this Command is scheduled to run
void PrepareElevators::Execute()
{
	elevator1->SetSetpoint(0);
	elevator2->SetSetpoint(0);
	elevator3->SetSetpoint(0);
}

// Make this return true when this Command no longer needs to run execute()
bool PrepareElevators::IsFinished()
{
	return elevator1->OnTarget() && elevator2->OnTarget() && elevator3->OnTarget();
}

// Called once after isFinished returns true
void PrepareElevators::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PrepareElevators::Interrupted()
{

}
