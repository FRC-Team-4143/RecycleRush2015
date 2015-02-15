#ifndef BinArmOut_H
#define BinArmOut_H

#include "WPILib.h"

class BinArmOut: public Command
{
public:
	BinArmOut();
	BinArmOut(double distance);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

	double setpoint;
	PIDController* arm;
	double current;
};

#endif
