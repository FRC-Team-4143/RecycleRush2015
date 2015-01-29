#include "GyroSub.h"
//#include "../Commands/ShowGyro.h"

GyroSub::GyroSub() : Subsystem("GyroSub") {
	std::cout << "GyroSub::GyroSub" << std::endl;
}

void GyroSub::InitDefaultCommand() {
	std::cout << "GyroSub::InitDefaultCommand" << std::endl;
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new ShowGyro());
}

// Put methods for controlling this subsystem here.
// Call these from Commands.

double GyroSub::GetHeading() {
	return theGyro()->GetYaw();
}

std::string GyroSub::GetStatus() {
	auto p = theGyro()->GetPitch();
	auto r = theGyro()->GetRoll();
	auto y = theGyro()->GetYaw();
	char sz[256];
	sprintf(sz, "Pitch: %f, Roll: %f, Yaw: %f", p, r, y);
	return sz;
}
