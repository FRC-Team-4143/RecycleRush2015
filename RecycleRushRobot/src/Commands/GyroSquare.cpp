#include "GyroSquare.h"
#include "Drive.h"
#include "RotateBy.h"

GyroSquare::GyroSquare() {
	for (auto ii = 0; ii < 4; ii++) {
		AddSequential(new Drive(0.5, 0, 0, true, 1));
		AddSequential(new RotateBy("Rotate Right 90", 90));
	}
}
