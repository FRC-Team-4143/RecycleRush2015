#ifndef ClampClaw_H
#define ClampClaw_H

#include "WPILib.h"

class ClampClaw: public Command
{
public:
	ClampClaw();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
