#ifndef SCRIPTBINBURGLAR_H
#define SCRIPTBINBURGLAR_H

#include <Commands/Command.h>
#include "WPILib.h"

class ScriptBinBurglar: public Command
{
public:
	ScriptBinBurglar(const char* name, float direction, float seconds);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	float _direction;
	float _seconds;
};

#endif
