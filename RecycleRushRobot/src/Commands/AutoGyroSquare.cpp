#include "AutoGyroSquare.h"
#include "Drive.h"
#include "RotateBy.h"

AutoGyroSquare::AutoGyroSquare()
{
	for (int i = 0; i < 4; i++){
		AddSequential(new Drive(0.5, 0, 0, true, 1));
		AddSequential(new RotateBy("Turn Right", 90));
	}

}
