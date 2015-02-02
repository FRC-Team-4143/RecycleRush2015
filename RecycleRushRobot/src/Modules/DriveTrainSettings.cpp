// ==========================================================================
// DriveTrainSettings class
//
// FRC 4143 "MARS WARS"
// ==========================================================================
// 2015-02-01 JKSalmon - Initial development
// ==========================================================================
#include "DriveTrainSettings.h"
#include "../Constants.h"
#include "../Logger.h"
#include "../Robot.h"
#include "../Subsystems/DriveTrain.h"
#include <WPILib.h>

const double AVERAGE_VOLTAGE_BASE = 2.5;

// ==========================================================================

DriveTrainSettings::DriveTrainSettings() {
}

// ==========================================================================

void DriveTrainSettings::LoadSettings() {
	LOG("DriveTrainSettings::LoadSettings");

	// Load the positions from Preferences.
	auto prefs = Preferences::GetInstance();
	auto FLPosition = prefs->GetDouble(Constants::FL_POS_NAME, Constants::FL_POS_DEFAULT);
	auto FRPosition = prefs->GetDouble(Constants::FR_POS_NAME, Constants::FR_POS_DEFAULT);
	auto RLPosition = prefs->GetDouble(Constants::RL_POS_NAME, Constants::RL_POS_DEFAULT);
	auto RRPosition = prefs->GetDouble(Constants::RR_POS_NAME, Constants::RR_POS_DEFAULT);

	LogSettings(FLPosition, FRPosition, RLPosition, RRPosition);

	// Set the drive train positions.
	Robot::driveTrain->SetOffsets(FLPosition, FRPosition, RLPosition, RRPosition);
}

// ==========================================================================

void DriveTrainSettings::SaveSettings() {
	LOG("DriveTrainSettings::SaveSettings");

	// Get the current steering positions from the drive train.
	auto FLPosition = Robot::driveTrain->frontLeftPos->GetAverageVoltage() - AVERAGE_VOLTAGE_BASE;
	auto FRPosition = Robot::driveTrain->frontRightPos->GetAverageVoltage() - AVERAGE_VOLTAGE_BASE;
	auto RLPosition = Robot::driveTrain->rearLeftPos->GetAverageVoltage() - AVERAGE_VOLTAGE_BASE;
	auto RRPosition = Robot::driveTrain->rearRightPos->GetAverageVoltage() - AVERAGE_VOLTAGE_BASE;

	LogSettings(FLPosition, FRPosition, RLPosition, RRPosition);

	// Save the positions to Preferences.
	auto prefs = Preferences::GetInstance();
	prefs->PutDouble(Constants::FL_POS_NAME, FLPosition);
	prefs->PutDouble(Constants::FR_POS_NAME, FRPosition);
	prefs->PutDouble(Constants::RL_POS_NAME, RLPosition);
	prefs->PutDouble(Constants::RR_POS_NAME, RRPosition);
	prefs->Save();

	// Set the drive train positions.
	Robot::driveTrain->SetOffsets(FLPosition, FRPosition, RLPosition, RRPosition);
}

// ==========================================================================

void DriveTrainSettings::LogSettings(double fl, double fr, double rl, double rr) {
	char sz[256];
	sprintf(sz, "Wheel Positions: FL %f, FR %f, RL %f, RR %f", fl, fr, rl, rr);
	LOG(sz);
}

// ==========================================================================
