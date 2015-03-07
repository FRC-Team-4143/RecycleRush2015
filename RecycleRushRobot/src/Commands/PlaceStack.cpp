#include "PlaceStack.h"
#include "Robot.h"

PlaceStack::PlaceStack()
{
	Requires(Robot::completeElevator);
}

// Called just before this Command runs the first time
void PlaceStack::Initialize()
{
	Robot::completeElevator->PlaceStack();
}

// Called repeatedly when this Command is scheduled to run
void PlaceStack::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool PlaceStack::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void PlaceStack::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PlaceStack::Interrupted()
{

}
