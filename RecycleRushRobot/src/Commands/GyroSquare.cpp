#include "GyroSquare.h"
#include "Drive.h"
#include "RotateBy.h"

GyroSquare::GyroSquare() {
	driveSpeed = SmartDashboard::GetNumber("Gyro-speed");
	driveTime = SmartDashboard::GetNumber("Gyro-time");

	for (auto ii = 0; ii < 4; ii++) {
		AddSequential(new Drive(driveSpeed, 0, 0, true, driveTime));
		AddSequential(new RotateBy("Rotate Right 90", 90));
	}
}
