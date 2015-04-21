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
	void Hold();
private:
	DoubleSolenoid* theSolenoid;
	DoubleSolenoid::Value theLastState;
};

#endif
