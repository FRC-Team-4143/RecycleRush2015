#include "GyroSub.h"

// ==========================================================================

GyroSub::GyroSub() : Subsystem("GyroSub") {
	std::cout << "GyroSub::GyroSub" << std::endl;
}

// ==========================================================================

void GyroSub::InitDefaultCommand() {
	std::cout << "GyroSub::InitDefaultCommand" << std::endl;
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MyCommand());
}

// ==========================================================================
// PIDSource methods
// ==========================================================================

double GyroSub::PIDGet() {
	return theGyro()->GetYaw();
}

// ==========================================================================
// Put methods for controlling this subsystem here.
// Call these from Commands.
// ==========================================================================

double GyroSub::GetHeading() {
	return theGyro()->GetCompassHeading();
}
