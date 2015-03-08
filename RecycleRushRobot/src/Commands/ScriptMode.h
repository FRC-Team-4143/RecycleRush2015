#ifndef SCRIPTMODE_H
#define SCRIPTMODE_H

#include <Commands/Command.h>
#include "WPILib.h"

class ScriptMode: public Command
{
public:
	ScriptMode(const char* name, int mode);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	int _mode;
};

#endif
