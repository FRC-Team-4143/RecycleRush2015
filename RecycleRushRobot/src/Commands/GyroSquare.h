#ifndef GyroSquare_H
#define GyroSquare_H

#include "WPILib.h"

class GyroSquare: public CommandGroup
{
public:
	GyroSquare();

	double driveSpeed;
	double driveTime;
};

#endif
