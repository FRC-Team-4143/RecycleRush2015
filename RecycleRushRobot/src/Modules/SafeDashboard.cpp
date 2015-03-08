#include "SafeDashboard.h"

std::string SafeDashboard::GetString(std::string name, std::string defaultValue) {
	try {
		return SmartDashboard::GetString(name, defaultValue);
	}
	catch (...) {
		// SmartDashboard parameter does not exist; create it.
		SmartDashboard::PutString(name, defaultValue);
		return defaultValue;
	}
}
