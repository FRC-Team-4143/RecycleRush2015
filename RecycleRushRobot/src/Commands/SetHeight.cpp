#include <Commands/SetHeight.h>
#include "../Robot.h"

// ==========================================================================

SetHeight::SetHeight(float height, float seconds) : Command("SetHeight") {
	std::cout << "SetHeight::ctor" << std::endl;
	_seconds = seconds;
	_height = height;
}

// ==========================================================================
// Called just before this Command runs the first time

void SetHeight::Initialize() {
	SetTimeout (_seconds);
	Robot::completeElevator->SetHeight(_height);
}

// ==========================================================================
// Called repeatedly when this Command is scheduled to run

void SetHeight::Execute() {


}

// ==========================================================================
// Make this return true when this Command no longer needs to run Execute.

bool SetHeight::IsFinished() {
	return IsTimedOut();
}

// ==========================================================================
// Called once after isFinished returns true

void SetHeight::End() {
}

// ==========================================================================
// Called when another command which requires this subsystem is scheduled to run

void SetHeight::Interrupted() {
	End();
}
