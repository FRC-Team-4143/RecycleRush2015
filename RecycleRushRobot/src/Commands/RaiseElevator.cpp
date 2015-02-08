#include "RaiseElevator.h"
#include "../Robot.h"

RaiseElevator::RaiseElevator(ElevatorSub* elevator)
{
	Requires(elevator);
	RaiseElevator::elevator = elevator;
}

// Called just before this Command runs the first time
void RaiseElevator::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void RaiseElevator::Execute()
{
	elevator->GoUp();
}

// Make this return true when this Command no longer needs to run execute()
bool RaiseElevator::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void RaiseElevator::End()
{
	elevator->HoldPosition();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RaiseElevator::Interrupted()
{
	elevator->HoldPosition();
}
