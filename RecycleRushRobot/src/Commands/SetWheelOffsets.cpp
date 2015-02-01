#include "SetWheelOffsets.h"
#include "../Robot.h"
#include <WPILib.h>

// ==========================================================================

SetWheelOffsets::SetWheelOffsets() {
	SetRunWhenDisabled(true);
}

// ==========================================================================
// Called just before this Command runs the first time

void SetWheelOffsets::Initialize() {
	if (DriverStation::GetInstance()->IsDisabled()) {
		FLOffset = Robot::driveTrain->frontLeftPos->GetAverageVoltage() - 2.5;
		FROffset = Robot::driveTrain->frontRightPos->GetAverageVoltage() - 2.5;
		RLOffset = Robot::driveTrain->rearLeftPos->GetAverageVoltage() - 2.5;
		RROffset = Robot::driveTrain->rearRightPos->GetAverageVoltage() - 2.5;

		auto prefs = Preferences::GetInstance();
		prefs->PutDouble("FLOff", FLOffset);
		prefs->PutDouble("FROff", FROffset);
		prefs->PutDouble("RLOff", RLOffset);
		prefs->PutDouble("RROff", RROffset);
		prefs->Save();

		Robot::driveTrain->SetOffsets(FLOffset, FROffset, RLOffset, RROffset);

		SetTimeout(2);
	}
	else {
		SetTimeout(0);
	}
}

// ==========================================================================
// Called repeatedly when this Command is scheduled to run

void SetWheelOffsets::Execute() {
}

// ==========================================================================
// Make this return true when this Command no longer needs to run Execute.

bool SetWheelOffsets::IsFinished() {
	return IsTimedOut();
}

// ==========================================================================
// Called once after IsFinished returns true

void SetWheelOffsets::End() {
}

// ==========================================================================
// Called when another command which requires this subsystem is scheduled to run

void SetWheelOffsets::Interrupted() {
}

// ==========================================================================
