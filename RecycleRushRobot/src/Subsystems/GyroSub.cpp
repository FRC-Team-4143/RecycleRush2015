#include "GyroSub.h"
#include "../Logger.h"

// ==========================================================================

GyroSub::GyroSub() : Subsystem("GyroSub") {
	LOG("GyroSub::GyroSub");
}

// ==========================================================================

void GyroSub::InitDefaultCommand() {
	LOG("GyroSub::InitDefaultCommand");
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

// ==========================================================================

bool GyroSub::IsCalibrating() {
	return theGyro()->IsCalibrating();
}

// ==========================================================================

void GyroSub::ResetGyro() {
	theGyro()->ZeroYaw();
}

// ==========================================================================
