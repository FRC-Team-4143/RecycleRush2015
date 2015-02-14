#ifndef Pneumatics_H
#define Pneumatics_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class Pneumatics: public Subsystem
{
private:

public:
	Pneumatics();
	void InitDefaultCommand();
	void forward();
	void reverse();
	void stop();

	DoubleSolenoid* solenoid;
};

#endif
