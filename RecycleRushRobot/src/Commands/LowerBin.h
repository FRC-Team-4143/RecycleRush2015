#ifndef LowerBin_H
#define LowerBin_H

#include "WPILib.h"

class LowerBin: public Command
{
public:
	LowerBin(double distance);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

	double dist;
	double current;
	double setpoint;
};

#endif
