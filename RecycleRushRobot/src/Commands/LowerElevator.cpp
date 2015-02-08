#include "LowerElevator.h"
#include "../Robot.h"

LowerElevator::LowerElevator(ElevatorSub* elevator)
{
	Requires(elevator);
	LowerElevator::elevator = elevator;
}

// Called just before this Command runs the first time
void LowerElevator::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void LowerElevator::Execute()
{
	elevator->GoDown();
}

// Make this return true when this Command no longer needs to run execute()
bool LowerElevator::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void LowerElevator::End()
{
	elevator->HoldPosition();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LowerElevator::Interrupted()
{
	elevator->HoldPosition();
}
