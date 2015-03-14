#include <Commands/BinDownTimed.h>
#include "../Robot.h"

// ==========================================================================

BinDownTimed::BinDownTimed(double seconds) : Command("Bin Down Timed") {
	std::cout << "BinDownTimed::ctor" << std::endl;

	Requires(Robot::completeElevator);
	_seconds = seconds;
}

// ==========================================================================
// Called just before this Command runs the first time

void BinDownTimed::Initialize() {
	SetTimeout (_seconds);
}

// ==========================================================================
// Called repeatedly when this Command is scheduled to run

void BinDownTimed::Execute() {

		Robot::completeElevator->MoveElevator(-1);

}

// ==========================================================================
// Make this return true when this Command no longer needs to run Execute.

bool BinDownTimed::IsFinished() {
	return IsTimedOut();
}

// ==========================================================================
// Called once after isFinished returns true

void BinDownTimed::End() {
}

// ==========================================================================
// Called when another command which requires this subsystem is scheduled to run

void BinDownTimed::Interrupted() {
	End();
}
