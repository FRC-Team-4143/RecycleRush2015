#ifndef ArmOut_H
#define ArmOut_H

#include "WPILib.h"

class ArmOut: public Command
{
public:
	ArmOut();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
