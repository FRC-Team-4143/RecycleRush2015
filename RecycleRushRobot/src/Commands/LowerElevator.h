#ifndef LowerElevator_H
#define LowerElevator_H

#include "WPILib.h"

class LowerElevator: public Command
{
public:
	LowerElevator();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
