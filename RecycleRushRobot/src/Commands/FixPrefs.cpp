#include "Commands/FixPrefs.h"
#include "../Constants.h"
#include "../Robot.h"
#include <WPILib.h>

// ==========================================================================

FixPrefs::FixPrefs() : Command("Show Prefs") {
	SetRunWhenDisabled(true);
}

// ==========================================================================
// Called just before this Command runs the first time

void FixPrefs::Initialize() {
	std::cout << "FixPrefs::Initialize" << std::endl;
	// List all preferences
	auto prefs = Preferences::GetInstance();
	prefs->Remove("testDouble");
	prefs->Remove("TestFloat");
	prefs->Remove("testLong");
	prefs->Remove("testString");
	prefs->Remove("test");
	prefs->Remove("RL-Pos");
	prefs->Remove("RR-Pos");
	prefs->Save();
	std::cout << "NAME: " << Constants::FL_POS_NAME << std::endl;
	//prefs->PutDouble(Constants::FL_POS_NAME, 0.0);
	//prefs->PutDouble(Constants::FR_POS_NAME, 0.0);
	//prefs->PutDouble(Constants::RL_POS_NAME, 0.0);
	//prefs->PutDouble(Constants::RR_POS_NAME, 0.0);
	prefs->Save();
}

// ==========================================================================
// Called repeatedly when this Command is scheduled to run

void FixPrefs::Execute() {
}

// ==========================================================================
// Make this return true when this Command no longer needs to run Execute.

bool FixPrefs::IsFinished() {
	return true;
}

// ==========================================================================
// Called once after IsFinished returns true

void FixPrefs::End() {
}

// ==========================================================================
// Called when another command which requires this subsystem is scheduled to run

void FixPrefs::Interrupted() {
}

// ==========================================================================
