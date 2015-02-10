#include "ResetAllEncoders.h"
#include "../Robot.h"

ResetAllEncoders::ResetAllEncoders()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	SetRunWhenDisabled(true);

}

// Called just before this Command runs the first time
void ResetAllEncoders::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void ResetAllEncoders::Execute()
{
	RobotMap::toteElevator1Pos->Reset();
	RobotMap::toteElevator2Pos->Reset();
	RobotMap::toteElevator3Pos->Reset();
}

// Make this return true when this Command no longer needs to run execute()
bool ResetAllEncoders::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void ResetAllEncoders::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ResetAllEncoders::Interrupted()
{

}
