#ifndef ReleaseClaw_H
#define ReleaseClaw_H

#include "WPILib.h"

class ReleaseClaw: public Command
{
public:
	ReleaseClaw();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
