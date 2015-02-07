#include "GyroSquare.h"
#include "Drive.h"
#include "RotateBy.h"

GyroSquare::GyroSquare() {
	auto driveStraight = new Drive(0.5, 0, 0, true, 1);
	auto rotateRight90 = new RotateBy("Rotate Right 90", 90);

	for (auto ii = 0; ii < 4; ii++) {
		AddSequential(driveStraight);
		AddSequential(rotateRight90);
	}
}
