#ifndef BURGLAROFF_H
#define BURGLAROFF_H

#include "WPILib.h"

class BurglarOff: public Command
{
public:
	BurglarOff();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
