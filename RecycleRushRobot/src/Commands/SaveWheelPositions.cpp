#include "Commands/SaveWheelPositions.h"
#include "../Modules/DriveTrainSettings.h"
#include "../Constants.h"
#include "../Robot.h"
#include <WPILib.h>

// ==========================================================================

SaveWheelPositions::SaveWheelPositions() : Command("Save Wheel Positions") {
	SetRunWhenDisabled(true);
}

// ==========================================================================
// Called just before this Command runs the first time

void SaveWheelPositions::Initialize() {
	if (DriverStation::GetInstance()->IsDisabled()) {
		DriveTrainSettings::SaveSettings();
		SetTimeout(2);
	}
	else {
		SetTimeout(0);
	}
}

// ==========================================================================
// Called repeatedly when this Command is scheduled to run

void SaveWheelPositions::Execute() {
}

// ==========================================================================
// Make this return true when this Command no longer needs to run Execute.

bool SaveWheelPositions::IsFinished() {
	return IsTimedOut();
}

// ==========================================================================
// Called once after IsFinished returns true

void SaveWheelPositions::End() {
}

// ==========================================================================
// Called when another command which requires this subsystem is scheduled to run

void SaveWheelPositions::Interrupted() {
}

// ==========================================================================
