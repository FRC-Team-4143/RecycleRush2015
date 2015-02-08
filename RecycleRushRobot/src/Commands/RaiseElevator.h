#ifndef RaiseElevator_H
#define RaiseElevator_H

#include "WPILib.h"
#include "../Subsystems/ElevatorSub.h"

class RaiseElevator: public Command
{
public:
	RaiseElevator(ElevatorSub* elevator);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

	ElevatorSub* elevator;
};

#endif
