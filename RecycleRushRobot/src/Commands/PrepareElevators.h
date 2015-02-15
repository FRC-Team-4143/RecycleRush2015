#ifndef PrepareElevators_H
#define PrepareElevators_H

#include "WPILib.h"

class PrepareElevators: public Command
{
public:
	PrepareElevators();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

	PIDController* elevator1;
	PIDController* elevator2;
	PIDController* elevator3;
};

#endif
