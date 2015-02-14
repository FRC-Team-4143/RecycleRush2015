#ifndef BinArmOut_H
#define BinArmOut_H

#include "WPILib.h"

class BinArmOut: public Command
{
public:
	BinArmOut();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

	float setpoint;
	PIDController* arm;
};

#endif
