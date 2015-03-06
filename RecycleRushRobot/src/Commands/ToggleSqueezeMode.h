#ifndef ToggleSqueezeMode_H
#define ToggleSqueezeMode_H

#include "WPILib.h"

class ToggleSqueezeMode: public Command
{
public:
	ToggleSqueezeMode();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
