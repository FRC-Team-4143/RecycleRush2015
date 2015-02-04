#include "Commands/ShowPrefs.h"
#include "../Modules/DriveTrainSettings.h"
#include "../Constants.h"
#include "../Robot.h"
#include <WPILib.h>

// ==========================================================================

ShowPrefs::ShowPrefs() : Command("Show Prefs") {
	std::cout << "ShowPrefs::ShowPrefs" << std::endl;
	SetRunWhenDisabled(true);
}

// ==========================================================================
// Called just before this Command runs the first time

void ShowPrefs::Initialize() {
	std::cout << "ShowPrefs::Initialize" << std::endl;
	// List all preferences
	auto prefs = Preferences::GetInstance();
	auto keys = prefs->GetKeys();
	std::cout << "[DEBUG] Keys:" << std::endl;
	for (auto iter = keys.begin(); iter != keys.end(); iter++) {
		auto value = prefs->GetString((*iter).c_str());
		std::cout << "[DEBUG] " << *iter << ": " << value << std::endl;
	}
}

// ==========================================================================
// Called repeatedly when this Command is scheduled to run

void ShowPrefs::Execute() {
}

// ==========================================================================
// Make this return true when this Command no longer needs to run Execute.

bool ShowPrefs::IsFinished() {
	return true;
}

// ==========================================================================
// Called once after IsFinished returns true

void ShowPrefs::End() {
}

// ==========================================================================
// Called when another command which requires this subsystem is scheduled to run

void ShowPrefs::Interrupted() {
}

// ==========================================================================
