#ifndef LowerAllElevators_H
#define LowerAllElevators_H

#include "WPILib.h"

class LowerAllElevators: public Command
{
public:
	LowerAllElevators();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

	SpeedController* motor1;
	SpeedController* motor2;
	SpeedController* motor3;
	SpeedController* motor4;

	PowerDistributionPanel* pdp;
};

#endif
