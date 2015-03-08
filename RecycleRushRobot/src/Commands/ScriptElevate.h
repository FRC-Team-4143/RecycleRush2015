#ifndef SCRIPTELEVATE_H
#define SCRIPTELEVATE_H

#include <Commands/Command.h>
#include "WPILib.h"

class ScriptElevate: public Command
{
public:
	ScriptElevate(const char* name, float axis, float seconds);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	float _axis;
	float _seconds;
};

#endif
