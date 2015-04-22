#ifndef BURGLARUP_H
#define BURGLARUP_H

#include "WPILib.h"

class BurglarUp: public Command
{
public:
	BurglarUp();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
