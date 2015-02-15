#ifndef BINARMIN_H
#define BINARMIN_H

#include "WPILib.h"

class BinArmIn: public Command
{
public:
	BinArmIn(double distance);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

	double setpoint;
	PIDController* arm;
};

#endif
