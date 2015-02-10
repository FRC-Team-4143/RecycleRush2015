#include <Commands/Sleep.h>
#include "../Robot.h"

// ==========================================================================

Sleep::Sleep(double seconds) : Command("Sleep") {
	std::cout << "Sleep::ctor" << std::endl;
	_seconds = seconds;
}

// ==========================================================================
// Called just before this Command runs the first time

void Sleep::Initialize() {
	SetTimeout (_seconds);
}

// ==========================================================================
// Called repeatedly when this Command is scheduled to run

void Sleep::Execute() {


}

// ==========================================================================
// Make this return true when this Command no longer needs to run Execute.

bool Sleep::IsFinished() {
	return IsTimedOut();
}

// ==========================================================================
// Called once after isFinished returns true

void Sleep::End() {
}

// ==========================================================================
// Called when another command which requires this subsystem is scheduled to run

void Sleep::Interrupted() {
	End();
}
