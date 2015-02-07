#include "GyroSquare.h"
#include "RotateBy.h"

GyroSquare::GyroSquare() {
	auto rotateRight90 = new RotateBy("Rotate Right 90", 90);
	//auto driveStraight = new ...

	for (auto ii = 0; ii < 4; ii++) {
		//AddSequential(driveStraight);
		AddSequential(rotateRight90);
	}
}
