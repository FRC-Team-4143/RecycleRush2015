#ifndef ArmIn_H
#define ArmIn_H

#include "WPILib.h"

class ArmIn: public Command
{
public:
	ArmIn();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
