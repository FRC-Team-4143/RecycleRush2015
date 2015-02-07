#ifndef RaiseElevator_H
#define RaiseElevator_H

#include "WPILib.h"

class RaiseElevator: public Command
{
public:
	RaiseElevator();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
