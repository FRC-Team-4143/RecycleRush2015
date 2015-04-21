#ifndef Pneumatics_H
#define Pneumatics_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class Pneumatics: public Subsystem
{
public:
	Pneumatics();
	void InitDefaultCommand();
	void Forward();
	void Reverse();
	void Stop();
private:
	DoubleSolenoid* theSolenoid;
};

#endif
