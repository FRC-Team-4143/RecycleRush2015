#include <Commands/BinUpTimed.h>
#include "../Robot.h"

// ==========================================================================

BinUpTimed::BinUpTimed(double seconds) : Command("Bin Up Timed") {
	std::cout << "BinUpTimed::ctor" << std::endl;

	Requires(Robot::binElevator);
	_seconds = seconds;
}

// ==========================================================================
// Called just before this Command runs the first time

void BinUpTimed::Initialize() {
	SetTimeout (_seconds);
}

// ==========================================================================
// Called repeatedly when this Command is scheduled to run

void BinUpTimed::Execute() {

		Robot::binElevator->MoveUp(1);

}

// ==========================================================================
// Make this return true when this Command no longer needs to run Execute.

bool BinUpTimed::IsFinished() {
	return IsTimedOut();
}

// ==========================================================================
// Called once after isFinished returns true

void BinUpTimed::End() {
}

// ==========================================================================
// Called when another command which requires this subsystem is scheduled to run

void BinUpTimed::Interrupted() {
	End();
}
