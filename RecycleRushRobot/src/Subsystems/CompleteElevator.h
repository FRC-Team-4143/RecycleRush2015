#ifndef CompleteElevator_H
#define CompleteElevator_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class CompleteElevator: public Subsystem
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	CompleteElevator();
	void InitDefaultCommand();
	void MoveElevator(float setpoint);

	PIDController*     toteElevator1PID;
	PIDController*     toteElevator2PID;
	PIDController*     toteElevator3PID;
};

#endif
