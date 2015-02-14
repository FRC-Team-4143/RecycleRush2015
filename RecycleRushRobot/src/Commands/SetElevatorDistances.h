#ifndef SetElevatorDistances_H
#define SetElevatorDistances_H

#include "WPILib.h"

class SetElevatorDistances: public Command
{
public:
	SetElevatorDistances();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

	Preferences* prefs;
	double distance4_3;
	double distance3_2;
	double distance2_1;
};

#endif
