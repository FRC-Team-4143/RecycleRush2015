#ifndef WaitForRelease_H
#define WaitForRelease_H

#include "WPILib.h"

class WaitForRelease: public Command
{
public:
	WaitForRelease();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

};

#endif
