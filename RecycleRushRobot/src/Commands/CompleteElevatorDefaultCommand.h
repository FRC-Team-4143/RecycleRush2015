#ifndef CompleteElevatorDefaultCommand_H
#define CompleteElevatorDefaultCommand_H

#include "WPILib.h"

class CompleteElevatorDefaultCommand: public Command
{
public:
	CompleteElevatorDefaultCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
