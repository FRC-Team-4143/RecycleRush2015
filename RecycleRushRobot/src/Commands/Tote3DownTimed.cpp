#include <Commands/Tote3DownTimed.h>
#include "../Robot.h"

// ==========================================================================

Tote3DownTimed::Tote3DownTimed(double seconds) : Command("Tote 3 Down Timed") {
	std::cout << "Tote3DownTimed::ctor" << std::endl;

	Requires(Robot::completeElevator);
	_seconds = seconds;
}

// ==========================================================================
// Called just before this Command runs the first time

void Tote3DownTimed::Initialize() {
	SetTimeout (_seconds);
}

// ==========================================================================
// Called repeatedly when this Command is scheduled to run

void Tote3DownTimed::Execute() {

		Robot::completeElevator->MoveElevator(1);

}

// ==========================================================================
// Make this return true when this Command no longer needs to run Execute.

bool Tote3DownTimed::IsFinished() {
	return IsTimedOut();
}

// ==========================================================================
// Called once after isFinished returns true

void Tote3DownTimed::End() {
}

// ==========================================================================
// Called when another command which requires this subsystem is scheduled to run

void Tote3DownTimed::Interrupted() {
	End();
}
