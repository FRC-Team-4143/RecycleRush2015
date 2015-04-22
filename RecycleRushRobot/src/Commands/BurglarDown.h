#ifndef BURGLARDOWN_H
#define BURGLARDOWN_H

#include "WPILib.h"

class BurglarDown: public Command
{
public:
	BurglarDown();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
