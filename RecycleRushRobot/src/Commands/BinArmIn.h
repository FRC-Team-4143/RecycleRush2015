#ifndef BinArmIn_H
#define BinArmIn_H

#include "WPILib.h"

class BinArmIn: public Command
{
public:
	BinArmIn();
	BinArmIn(double distance);
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
