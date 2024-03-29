#include <Commands/Tote3UpTimed.h>
#include "../Robot.h"

// ==========================================================================

Tote3UpTimed::Tote3UpTimed(double seconds) : Command("Tote 3 Up Timed") {
	std::cout << "Tote3UpTimed::ctor" << std::endl;

	Requires(Robot::completeElevator);
	_seconds = seconds;
}

// ==========================================================================
// Called just before this Command runs the first time

void Tote3UpTimed::Initialize() {
	SetTimeout (_seconds);
}

// ==========================================================================
// Called repeatedly when this Command is scheduled to run

void Tote3UpTimed::Execute() {

		Robot::completeElevator->MoveElevator(1);

}

// ==========================================================================
// Make this return true when this Command no longer needs to run Execute.

bool Tote3UpTimed::IsFinished() {
	return IsTimedOut();
}

// ==========================================================================
// Called once after isFinished returns true

void Tote3UpTimed::End() {
}

// ==========================================================================
// Called when another command which requires this subsystem is scheduled to run

void Tote3UpTimed::Interrupted() {
	End();
}
