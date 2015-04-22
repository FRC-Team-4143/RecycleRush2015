#ifndef PNEUMASTASIS_H
#define PNEUMASTASIS_H

#include <Commands/Command.h>
#include "WPILib.h"

class PneumaStasis: public Command
{
public:
	PneumaStasis(const char* name);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
};

#endif
