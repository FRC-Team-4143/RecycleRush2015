#include "CompleteElevatorDefaultCommand.h"
#include "../Robot.h"

CompleteElevatorDefaultCommand::CompleteElevatorDefaultCommand()
{
	Requires(Robot::completeElevator);
}

// Called just before this Command runs the first time
void CompleteElevatorDefaultCommand::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void CompleteElevatorDefaultCommand::Execute()
{
	auto rightAxisValue = Robot::oi->GetDriverRightTrigger();
	auto leftAxisValue = Robot::oi->GetDriverLeftTrigger();
	Robot::completeElevator->MoveElevator(rightAxisValue - leftAxisValue);

}

// Make this return true when this Command no longer needs to run execute()
bool CompleteElevatorDefaultCommand::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void CompleteElevatorDefaultCommand::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CompleteElevatorDefaultCommand::Interrupted()
{

}
