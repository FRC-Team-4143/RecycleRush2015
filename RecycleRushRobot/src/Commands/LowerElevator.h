#ifndef LowerElevator_H
#define LowerElevator_H

#include "WPILib.h"
#include "../Subsystems/ElevatorSub.h"

class LowerElevator: public Command
{
public:
	LowerElevator(ElevatorSub* elevator);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

	ElevatorSub* elevator;
};

#endif
