#include "Raise1Level.h"
#include "Robot.h"

Raise1Level::Raise1Level()
{
	Requires(Robot::completeElevator);
}

// Called just before this Command runs the first time
void Raise1Level::Initialize()
{
	Robot::completeElevator->MoveElevator(SmartDashboard::GetNumber("Raise1Level-distance"));
}

// Called repeatedly when this Command is scheduled to run
void Raise1Level::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool Raise1Level::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void Raise1Level::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Raise1Level::Interrupted()
{

}
